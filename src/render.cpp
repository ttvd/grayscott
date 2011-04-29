/*
 *  render.cpp
 *  Gray-Scott Reaction Diffusion system.
 *
 *  Reaction-diffusion simulation. Rendering of textures and textured objects.
 *
 *  Created by radix on 04/29/11.
 *  Copyright Mykola Konyk, <mykola@konyk.org>, 2011.
 *  
 *  This code is under Microsoft Reciprocal License (Ms-RL)
 *  Please see http://www.opensource.org/licenses/ms-rl.html
 *
 *  Important points about the license (from Ms-RL):
 *
 *  [A] For any file you distribute that contains code from the software (in source code or binary format), you must provide 
 *  recipients the source code to that file along with a copy of this license, which license will govern that file. 
 *  You may license other files that are entirely your own work and do not contain code from the software under any terms 
 *  you choose.
 *
 *  [B] No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
 *
 *  [C] If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your 
 *  patent license from such contributor to the software ends automatically.
 *
 *  [D] If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices 
 *  that are present in the software.
 *
 *  [E] If you distribute any portion of the software in source code form, you may do so only under this license by including a
 *  complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object 
 *  code form, you may only do so under a license that complies with this license.
 *
 *  [F] The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees 
 *  or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent 
 *  permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular 
 *  purpose and non-infringement.
 *
 */

#include <render.h>
#include <window.h>
#include <framebuffer.h>

#include "ui_render.h"

#include <QtGui/QDockWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QMouseEvent>

#include <QtOpenGL/QGLShaderProgram>

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QSettings>

#include <QtCore/QDebug>

#if defined(Q_OS_WIN)
	#include <GL/glut.h>
#elif defined(Q_OS_MAC)
    #include <GLUT/glut.h>
#endif

namespace Comp5201Project
{
	//--
	static const float kF = 0.008f;
	static const float kK = 0.032f;

	static const float kDiffuseU = 0.18f;
	static const float kDiffuseV = 0.160f;

	static const float kTimestep = 2.5f;
	static const float kDistance = 1.5f;

	static const float kDuMin = 0.0f;
	static const float kDuMax = 0.3f;
	static const float kDuSliderScale = 1000.0f;

	static const float kDvMin = 0.0f;
	static const float kDvMax = 0.3f;
	static const float kDvSliderScale = 1000.0f;

	static const float kDistMin = 1.0f;
	static const float kDistMax = 3.0f;
	static const float kDistSliderScale = 1000.0f;

	static const float kStepMin = 1.0f;
	static const float kStepMax = 4.0f;
	static const float kStepSliderScale = 1000.0f;

	static const float kKMin = 0.0f;
	static const float kKMax = 0.3f;
	static const float kKSliderScale = 1000.0f;

	static const float kFMin = 0.0f;
	static const float kFMax = 0.3f;
	static const float kFSliderScale = 1000.0f;

	static const float kMouseRotationScale = 0.5f;

	static const float kDisplace = 0.5f;
	static const float kDisplaceSliderScale = 1000.0f;
	static const float kDisplaceMin = 0.0f;
	static const float kDisplaceMax = 2.5f;

	static const float kDiscard = 0.5f;
	static const float kDiscardSliderScale = 1000.0f;
	static const float kDiscardMin = 0.0f;
	static const float kDiscardMax = 1.0f;


	//--
	Render::Render(QWidget* parent) :
	QGLWidget(parent),
	m_sliderguard(false),
	m_initialized(false),
	m_started(false),
	m_paused(true),
	m_resized(false),
	m_frame_id(0),
	m_frame_delta(0.0f),
	m_total_time(0.0f),
	m_width(0),
	m_height(0),
	m_time_frame(NULL),
    m_timer_scene_update(NULL),
	m_shader_greyscott(0),
	m_shader_render2d(0),
	m_shader_render3d(0),
	m_fbo_greyscottresult(0),
	m_fbo_greyscottresult2(0),
	m_tex_initial_concentration(0),
	m_display_mode(0),
	m_distance(kDistance),
	m_timestep(kTimestep),
	m_automatictimestep(false),
	m_k(kK),
	m_f(kF),
	m_du(kDiffuseU),
	m_dv(kDiffuseV),
	m_render_mode(RenderMode::Render2d),
	m_mouse_position(0.0f, 0.0f),
	m_mouse_rotation(true),
	m_rotation_x(0.0f),
	m_rotation_y(0.0f),
	m_discard(0),
	m_displace(0),
	m_discard_size(kDiscard),
	m_displace_size(kDisplace)
	{
		m_parent = static_cast<Window*>(parent);

		// [rad] This should fix the flickering problem.
        setAttribute(Qt::WA_PaintOnScreen, true);
        setAttribute(Qt::WA_NoBackground);

		createSettings();

		// [rad] Create scene update timer.
        m_timer_scene_update = new QTimer(this);
        connect(m_timer_scene_update, SIGNAL(timeout()), this, SLOT(updateGL()));
        m_timer_scene_update->start(0);
	}	


	//--
	Render::Render(const QGLFormat& gl_format, QWidget* parent) :
	QGLWidget(gl_format, parent),
	m_sliderguard(false),
	m_initialized(false),
	m_started(false),
	m_paused(true),
	m_resized(false),
	m_frame_id(0),
	m_frame_delta(0.0f),
	m_total_time(0.0f),
	m_width(0),
	m_height(0),
	m_time_frame(NULL),
    m_timer_scene_update(NULL),
	m_shader_greyscott(0),
	m_shader_render2d(0),
	m_shader_render3d(0),
	m_fbo_greyscottresult(0),
	m_fbo_greyscottresult2(0),
	m_tex_initial_concentration(0),
	m_display_mode(0),
	m_distance(kDistance),
	m_timestep(kTimestep),
	m_automatictimestep(false),
	m_k(kK),
	m_f(kF),
	m_du(kDiffuseU),
	m_dv(kDiffuseV),
	m_render_mode(RenderMode::Render2d),
	m_mouse_position(0.0f, 0.0f),
	m_mouse_rotation(true),
	m_rotation_x(0.0f),
	m_rotation_y(0.0f),
	m_discard(0),
	m_displace(0),
	m_discard_size(kDiscard),
	m_displace_size(kDisplace)
	{
		m_parent = static_cast<Window*>(parent);

		// [rad] This should fix the flickering problem.
        setAttribute(Qt::WA_PaintOnScreen, true);
        setAttribute(Qt::WA_NoBackground);

		createSettings();

		// [rad] Create scene update timer.
        m_timer_scene_update = new QTimer(this);
        connect(m_timer_scene_update, SIGNAL(timeout()), this, SLOT(updateGL()));
        m_timer_scene_update->start(0);
	}	


	//--
	Render::~Render()
	{
		if(m_ui_render)
		{
			delete(m_ui_render);
		}

		if(m_time_frame)
        {
            delete(m_time_frame);
            m_time_frame = NULL;
        }

        if(m_tex_initial_concentration)
        {
        	glDeleteTextures(1, &m_tex_initial_concentration);
        }
	}


	//--
	void 
	Render::requestDock(Window* window, QDockWidget* dock)
	{
		Q_UNUSED(window);
		dock->setWidget(m_settings);
	}


	//--
	void 
	Render::setConcentrationMapU(const QImage& img)
	{
		m_concentration_u = img;
	}
        	

    //--
    void 
    Render::setConcentrationMapV(const QImage& img)
    {
    	m_concentration_v = img;
    }


	//--
	void
	Render::createShaders()
	{
		// [rad] Create greyscott shader.

		m_shader_greyscott = new QGLShaderProgram(this);

		if(!m_shader_greyscott->addShaderFromSourceFile(QGLShader::Vertex, ":shaders/greyscott.vert"))
        {
            qDebug() << "Vertex shader 'greyscott' was not found or failed to compile.";
            qDebug() << m_shader_greyscott->log();
        }

        if(!m_shader_greyscott->addShaderFromSourceFile(QGLShader::Fragment, ":shaders/greyscott.frag"))
        {
            qDebug() << "Fragment shader 'greyscott' was not found or failed to compile.";
            qDebug() << m_shader_greyscott->log();
        }


        // [rad] Create presentation shader.

		m_shader_render2d = new QGLShaderProgram(this);

		if(!m_shader_render2d->addShaderFromSourceFile(QGLShader::Vertex, ":shaders/render2d.vert"))
        {
            qDebug() << "Vertex shader 'render2d' was not found or failed to compile.";
            qDebug() << m_shader_render2d->log();
        }

        if(!m_shader_render2d->addShaderFromSourceFile(QGLShader::Fragment, ":shaders/render2d.frag"))
        {
            qDebug() << "Fragment shader 'render2d' was not found or failed to compile.";
            qDebug() << m_shader_render2d->log();
        }


        // [rad] Create 3d presenation shader.

		m_shader_render3d = new QGLShaderProgram(this);

		if(!m_shader_render3d->addShaderFromSourceFile(QGLShader::Vertex, ":shaders/render3d.vert"))
        {
            qDebug() << "Vertex shader 'render3d' was not found or failed to compile.";
            qDebug() << m_shader_render3d->log();
        }

        if(!m_shader_render3d->addShaderFromSourceFile(QGLShader::Fragment, ":shaders/render3d.frag"))
        {
            qDebug() << "Fragment shader 'render3d' was not found or failed to compile.";
            qDebug() << m_shader_render3d->log();
        }
	}


	//--
	void
	Render::createFBOs()
	{
        m_fbo_greyscottresult = new FrameBuffer(m_width, m_height, this);
        m_fbo_greyscottresult2 = new FrameBuffer(m_width, m_height, this);
	}


	//--
	void 
	Render::createSettings()
	{
		m_settings = new QWidget();
		m_ui_render = new Ui::render();
		m_ui_render->setupUi(m_settings);

		QObject::connect(m_ui_render->button_start, SIGNAL(clicked()), this, SLOT(buttonStart()));
		QObject::connect(m_ui_render->button_restart, SIGNAL(clicked()), this, SLOT(buttonRestart()));
		QObject::connect(m_ui_render->button_defaults, SIGNAL(clicked()), this, SLOT(buttonDefaults()));
		QObject::connect(m_ui_render->button_save, SIGNAL(clicked()), this, SLOT(buttonSaveImage()));
		QObject::connect(m_ui_render->button_saveconfig, SIGNAL(clicked()), this, SLOT(buttonSaveConfig()));
		QObject::connect(m_ui_render->button_loadconfig, SIGNAL(clicked()), this, SLOT(buttonLoadConfig()));

		m_ui_render->radio_rendering_u->toggle();		
		QObject::connect(m_ui_render->radio_rendering_u, SIGNAL(toggled(bool)), this, SLOT(radioModeU(bool)));
		QObject::connect(m_ui_render->radio_rendering_v, SIGNAL(toggled(bool)), this, SLOT(radioModeV(bool)));
		QObject::connect(m_ui_render->radio_rendering_changeu, SIGNAL(toggled(bool)), this, SLOT(radioModeDU(bool)));

		// [rad] Checkbox
		QObject::connect(m_ui_render->checkbox_discard, SIGNAL(toggled(bool)), this, SLOT(checkboxDiscard(bool)));
		QObject::connect(m_ui_render->checkbox_displace, SIGNAL(toggled(bool)), this, SLOT(checkboxDisplace(bool)));

		QString temp;

		QObject::connect(m_ui_render->edit_distance, SIGNAL(textChanged(const QString &)), this, SLOT(editDistance(const QString&)));
		temp.setNum(m_distance);
		m_ui_render->edit_distance->setText(temp);

		QObject::connect(m_ui_render->edit_timestep, SIGNAL(textChanged(const QString &)), this, SLOT(editTimestep(const QString&)));
		temp.setNum(m_timestep);
		m_ui_render->edit_timestep->setText(temp);

		QObject::connect(m_ui_render->edit_f, SIGNAL(textChanged(const QString &)), this, SLOT(editF(const QString&)));
		temp.setNum(m_f);
		m_ui_render->edit_f->setText(temp);

		QObject::connect(m_ui_render->edit_k, SIGNAL(textChanged(const QString &)), this, SLOT(editK(const QString&)));
		temp.setNum(m_k);
		m_ui_render->edit_k->setText(temp);

		QObject::connect(m_ui_render->edit_du, SIGNAL(textChanged(const QString &)), this, SLOT(editDu(const QString&)));
		temp.setNum(m_du);
		m_ui_render->edit_du->setText(temp);

		QObject::connect(m_ui_render->edit_dv, SIGNAL(textChanged(const QString &)), this, SLOT(editDv(const QString&)));
		temp.setNum(m_dv);
		m_ui_render->edit_dv->setText(temp);


		// [rad] Du slider.
		m_ui_render->slider_du->setRange(kDuMin * kDuSliderScale, kDuMax * kDuSliderScale);
		m_ui_render->slider_du->setValue(static_cast<int>(m_du * kDuSliderScale));
		QObject::connect(m_ui_render->slider_du, SIGNAL(valueChanged(int)), this, SLOT(sliderEventDu(int)));
		m_ui_render->label_du_min->setText(QString::number(kDuMin));		
		m_ui_render->label_du_max->setText(QString::number(kDuMax));
	
		// [rad] Dv slider.
		m_ui_render->slider_dv->setRange(kDvMin * kDvSliderScale, kDvMax * kDvSliderScale);
		m_ui_render->slider_dv->setValue(static_cast<int>(m_dv * kDvSliderScale));
		QObject::connect(m_ui_render->slider_dv, SIGNAL(valueChanged(int)), this, SLOT(sliderEventDv(int)));	
		m_ui_render->label_dv_min->setText(QString::number(kDvMin));		
		m_ui_render->label_dv_max->setText(QString::number(kDvMax));

		// [rad] Dist slider.
		m_ui_render->slider_dist->setRange(kDistMin * kDistSliderScale, kDistMax * kDistSliderScale);
		m_ui_render->slider_dist->setValue(static_cast<int>(m_distance * kDistSliderScale));
		QObject::connect(m_ui_render->slider_dist, SIGNAL(valueChanged(int)), this, SLOT(sliderEventDist(int)));
		m_ui_render->label_dist_min->setText(QString::number(kDistMin));		
		m_ui_render->label_dist_max->setText(QString::number(kDistMax));

		// [rad] Step slider.
		m_ui_render->slider_step->setRange(kStepMin * kStepSliderScale, kStepMax * kStepSliderScale);
		m_ui_render->slider_step->setValue(static_cast<int>(m_timestep * kStepSliderScale));
		QObject::connect(m_ui_render->slider_step, SIGNAL(valueChanged(int)), this, SLOT(sliderEventStep(int)));
		m_ui_render->label_step_min->setText(QString::number(kStepMin));		
		m_ui_render->label_step_max->setText(QString::number(kStepMax));

		// [rad] F slider.
		m_ui_render->slider_f->setRange(kFMin * kFSliderScale, kFMax * kFSliderScale);
		m_ui_render->slider_f->setValue(static_cast<int>(m_f * kFSliderScale));
		QObject::connect(m_ui_render->slider_f, SIGNAL(valueChanged(int)), this, SLOT(sliderEventF(int)));
		m_ui_render->label_f_min->setText(QString::number(kFMin));		
		m_ui_render->label_f_max->setText(QString::number(kFMax));

		// [rad] K slider.
		m_ui_render->slider_k->setRange(kKMin * kKSliderScale, kKMax * kKSliderScale);
		m_ui_render->slider_k->setValue(static_cast<int>(m_f * kKSliderScale));
		QObject::connect(m_ui_render->slider_k, SIGNAL(valueChanged(int)), this, SLOT(sliderEventK(int)));
		m_ui_render->label_k_min->setText(QString::number(kKMin));		
		m_ui_render->label_k_max->setText(QString::number(kKMax));

		// [rad] Discard slider.
		m_ui_render->slider_discard->setRange(kDiscardMin * kDiscardSliderScale, kDiscardMax * kDiscardSliderScale);
		m_ui_render->slider_discard->setValue(static_cast<int>(m_discard_size * kDiscardSliderScale));
		QObject::connect(m_ui_render->slider_discard, SIGNAL(valueChanged(int)), this, SLOT(sliderEventDiscard(int)));
		m_ui_render->label_discard_min->setText(QString::number(kDiscardMin));		
		m_ui_render->label_discard_max->setText(QString::number(kDiscardMax));

		// [rad] Displace slider.
		m_ui_render->slider_displace->setRange(kDisplaceMin * kDisplaceSliderScale, kDisplaceMax * kDisplaceSliderScale);
		m_ui_render->slider_displace->setValue(static_cast<int>(m_displace_size * kDisplaceSliderScale));
		QObject::connect(m_ui_render->slider_displace, SIGNAL(valueChanged(int)), this, SLOT(sliderEventDisplace(int)));
		m_ui_render->label_displace_min->setText(QString::number(kDisplaceMin));		
		m_ui_render->label_displace_max->setText(QString::number(kDisplaceMax));

		// [rad] Combobox.
		m_ui_render->combo_render->addItem("Render 2D");
		m_ui_render->combo_render->addItem("Render 3D Sphere");
		m_ui_render->combo_render->addItem("Render 3D Torus");
		m_ui_render->combo_render->addItem("Render 3D Teapot");
		QObject::connect(m_ui_render->combo_render, SIGNAL(currentIndexChanged (int)), this, SLOT(comboEventRender(int)));
		
	}


	//--
	void 
	Render::buttonSaveImage()
	{
		QString filename = QFileDialog::getSaveFileName(this, "Save reaction-diffusion simulation file", "", tr("Simulation images (*.bmp *.png *.jpg *.jpeg *.tiff)"));

		QImage image = grabFrameBuffer();

     	if(image.save(filename))
     	{
     		qDebug() << "Failed saving image.";
     	}
	}
    

    //--
    void 
    Render::buttonSaveConfig()
    {
    	QString filename = QFileDialog::getSaveFileName(this, "Save simulation configuration", "", tr("Simulation config (*.rdsim *.ini)"));

    	QSettings settings(filename, QSettings::IniFormat);

    	settings.setValue("distance", m_distance);
    	settings.setValue("timestep", m_timestep);
    	settings.setValue("du", m_du);
    	settings.setValue("dv", m_dv);
    	settings.setValue("k", m_k);
    	settings.setValue("f", m_f);
    }
    

    //--
    void 
    Render::buttonLoadConfig()
    {
    	QString filename = QFileDialog::getOpenFileName(this, "Open simulation configuration", "", tr("Simulation config (*.rdsim *.ini)"));

    	QSettings settings(filename, QSettings::IniFormat);

    	editDistance(settings.value("distance").toString());
        editTimestep(settings.value("timestep").toString());

       	editF(settings.value("f").toString());
        editK(settings.value("k").toString());

        editDu(settings.value("du").toString());
        editDv(settings.value("dv").toString());

        m_frame_id = 0;
    }


	//--
	void
	Render::buttonStart()
	{
		if(!m_started)
		{
			m_started = true;

			m_paused = false;
			m_ui_render->button_start->setText("Pause");
		}
		else
		{
			if(m_paused)
			{
				m_paused = false;
				m_ui_render->button_start->setText("Pause");
			}
			else
			{
				m_paused = true;
				m_ui_render->button_start->setText("Start");
			}
		}
	}


	//--
	void
	Render::buttonRestart()
	{
		m_paused = false;
		m_started = true;

		m_ui_render->button_start->setText("Pause");

		m_frame_id = 0;
	}


	//--
	void
	Render::buttonDefaults()
	{
		QString temp;

		//m_display_mode = 0;
		m_ui_render->radio_rendering_u->toggle();		

		m_distance = kDistance;
		temp.setNum(m_distance);
		m_ui_render->edit_distance->setText(temp);

		m_timestep = kTimestep;
		temp.setNum(m_timestep);
		m_ui_render->edit_timestep->setText(temp);

		m_f = kF;
		temp.setNum(m_f);
		m_ui_render->edit_f->setText(temp);

		m_k = kK;
		temp.setNum(m_k);
		m_ui_render->edit_k->setText(temp);

		m_du = kDiffuseU;
		temp.setNum(m_du);
		m_ui_render->edit_du->setText(temp);

		m_dv = kDiffuseV;
		temp.setNum(m_dv);
		m_ui_render->edit_dv->setText(temp);

		m_render_mode = RenderMode::Render2d;
		m_ui_render->combo_render->setCurrentIndex(0);

		m_displace_size = kDisplace;
		m_ui_render->slider_displace->setValue(static_cast<int>(m_displace_size * kDisplaceSliderScale));

		m_discard_size = kDisplace;
		m_ui_render->slider_discard->setValue(static_cast<int>(m_discard_size * kDiscardSliderScale));
	}

    //--
    void
    Render::update()
    {
        if(!m_frame_id)
		{
			m_total_time = 0.0f;
			
        	if(!m_initialized)
        	{
        		createShaders();
        		createFBOs();

        		m_initialized = true;
        	}

			// [rad] Very first frame, we need to produce initial concentration texture.

			QImage combined(m_concentration_v.size(), QImage::Format_ARGB32);

			for(int x = 0; x < m_concentration_v.width(); ++x)
     		{
     			for(int y = 0; y < m_concentration_v.height(); ++y)
     			{
     				int pixel_u = m_concentration_u.pixel(x, y);
     				int pixel_v = m_concentration_v.pixel(x, y);

     				// [rad] Store concentration of U in R channel and concentration of V in G channel.
     				combined.setPixel(x, y, qRgb(pixel_u, pixel_v, 0));
     			}
     		}

     		// [rad] Convert image to Qt GL friendly format.
			QImage gl_image = QGLWidget::convertToGLFormat(combined);

			if(gl_image.isNull())
			{
				qDebug() << "Cannot create initial combined concentration texture.";
			}

			// [rad] Create GL texture.

			if(m_tex_initial_concentration)
			{
				glDeleteTextures(1, &m_tex_initial_concentration);
			}

			glGenTextures(1, &m_tex_initial_concentration);
			glBindTexture(GL_TEXTURE_2D, m_tex_initial_concentration);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gl_image.width(), gl_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, gl_image.bits());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    		glBindTexture(GL_TEXTURE_2D, 0);
		}

		if(m_resized)
		{
			m_resized = false;

			if(m_fbo_greyscottresult)
        	{
        		m_fbo_greyscottresult->resize(m_width, m_height);
        	}

        	if(m_fbo_greyscottresult2)
	    	{
	    		m_fbo_greyscottresult2->resize(m_width, m_height);
	    	}

	    	m_frame_id = 0;
	    	return;
		}

    	int msec = 0;

    	if(!m_time_frame)
        {
            // [rad] Create frame time.
            m_time_frame = new QTime();
            m_time_frame->start();
        }
        else
        {
            msec = m_time_frame->elapsed();
            m_time_frame->restart();
        }

        // [rad] Compute frame delta (how much time this frame took).
        m_frame_delta = msec / 1000.0f;
        m_total_time += m_frame_delta;


        // [rad] Update frame label.
        m_ui_render->label_frame->setText(QString("Frame: ") + QString::number(m_frame_id));

        // [rad] Update time.
        m_ui_render->label_time->setText(QString("Time: ") + QString::number(m_total_time) + QString(" s"));

        ++m_frame_id;
    }


    //--
	void
	Render::resizeGL(int width, int height)
	{
		m_width = width;
        m_height = height;

        //const GLfloat range = 0.25f;

        if(!m_height)
        {
            m_height = 1;
        }

		glViewport(0, 0, m_width, m_height);

		m_resized = true;
	}


	//--
	void
	Render::initializeGL()
	{
		// [rad] Call parent's implementation (one we are trying to overload).
        QGLWidget::initializeGL();
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glShadeModel(GL_SMOOTH);
        glDisable(GL_LIGHTING);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 


		#if defined(Q_OS_WIN)
	        
        // [rad] Initialize glew.
        GLenum err = glewInit();
        if(GLEW_OK != err)
        {
            qDebug() << "Error initializing GLEW " << glewGetErrorString(err);
        }

        #endif       
	}


	//--
	void
	Render::paintGL()
	{
        if(!m_started)
		{
            return;
        }

        if(!m_paused)
        {
			update();
		}

		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		// [rad] We are going to render to an FBO (offscreen).
		if(m_frame_id % 2 == 0)
		{
			m_fbo_greyscottresult2->bind();
				m_shader_greyscott->bind();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult->attachmentColor());	
		}
		else
		{
			m_fbo_greyscottresult->bind();
				m_shader_greyscott->bind();

				glActiveTexture(GL_TEXTURE0);

				if(1 == m_frame_id)
				{
					glBindTexture(GL_TEXTURE_2D, m_tex_initial_concentration);	
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult2->attachmentColor());
				}
		}
    	
    			m_shader_greyscott->setUniformValue("tex0U", 0);

    			// [rad] Compute offsets for kernel sampling.
    			m_shader_greyscott->setUniformValue("step_width", (1.0f / static_cast<float>(m_width)));
    			m_shader_greyscott->setUniformValue("step_height", (1.0f / static_cast<float>(m_height)));

    			if(m_automatictimestep)
    			{
    				m_shader_greyscott->setUniformValue("timestep", m_frame_delta);
    			}
    			else
    			{
    				m_shader_greyscott->setUniformValue("timestep", m_timestep);
    			}
    			
    			
    			m_shader_greyscott->setUniformValue("du", m_du);
    			m_shader_greyscott->setUniformValue("dv", m_dv);
    			m_shader_greyscott->setUniformValue("distance", m_distance);
    			m_shader_greyscott->setUniformValue("k", m_k);
    			m_shader_greyscott->setUniformValue("f", m_f);

    			// [rad] Render Fullscreen Quad.
				glBegin(GL_QUADS);
		 
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(-1.0f, -1.0f, -1.0f);
		 
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(1.0f, -1.0f, -1.0f);
		 
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(1.0f, 1.0f, -1.0f);
		 
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(-1.0f, 1.0f, -1.0f);
		 
				glEnd();

				glBindTexture(GL_TEXTURE_2D, 0);
	    		glActiveTexture(GL_TEXTURE0);
	    	
	    	m_shader_greyscott->release();

		if(m_frame_id % 2 == 0)
		{
			m_fbo_greyscottresult2->release();
		}
		else
		{
			m_fbo_greyscottresult->release();
		}

	    

	    if(RenderMode::Render2d == m_render_mode)
	    {
	    	m_shader_render2d->bind();
		    glActiveTexture(GL_TEXTURE0);

		    if(m_frame_id % 2 == 0)
			{
				glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult2->attachmentColor());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult->attachmentColor());
			}

			m_shader_render2d->setUniformValue("tex0U", 0);
			m_shader_render2d->setUniformValue("display_mode", m_display_mode);

			glBegin(GL_QUADS);
	 
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
	 
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
	 
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);
	 
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
	 
			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE0);
			m_shader_render2d->release();

			glEnd();
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
	    }
	    else
	    {
	    	glClearColor(0.81, 0.92, 0.97, 1.0);
			 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			gluPerspective(45.0f, (float) m_width / (float) m_height, 200.0f, 400.0f);

			glMatrixMode(GL_MODELVIEW);

			glLoadIdentity();
			glPushMatrix();

			glTranslatef(0, 0, -300.0f);

			glRotatef(m_rotation_x, 0, 1, 0);
			glRotatef(m_rotation_y, 1, 0, 0);

			glScalef(25.0f, 25.0f, 25.0f);

			m_shader_render3d->bind();
		    glActiveTexture(GL_TEXTURE0);

		    if(m_frame_id % 2 == 0)
			{
				glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult2->attachmentColor());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, m_fbo_greyscottresult->attachmentColor());
			}

			
			m_shader_render3d->setUniformValue("tex0U", 0);

			m_shader_render3d->setUniformValue("enable_discard", m_discard);
			m_shader_render3d->setUniformValue("discard_limit", m_discard_size);

			m_shader_render3d->setUniformValue("enable_displacement", m_displace);
			m_shader_render3d->setUniformValue("displace_size", m_displace_size);

			switch(m_render_mode)
	    	{
	    		case RenderMode::Render3dTorus:
				{
					m_shader_render3d->setUniformValue("mapping_mode", 1);
					glutSolidTorus(1.0f, 2.5f, 100, 500);
				}
				break;

				case RenderMode::Render3dTeapot:
				{
					// [rad] No special mapping mode, teapot has UV coordinates.
					m_shader_render3d->setUniformValue("mapping_mode", 0);
					glutSolidTeapot(2.7f);

				}
				break;

				case RenderMode::Render3dSphere:
				{
					m_shader_render3d->setUniformValue("mapping_mode", 1);
					glutSolidSphere(3.3, 1000, 1000);
				}
				break;
			} 

			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE0);
			m_shader_render3d->release();
	 
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
	    }
	}

	//--
	void 
	Render::radioModeU(bool b)
	{
		if(b)
		{
			m_display_mode = 0;
		}	
	}


	//--
    void 
    Render::radioModeV(bool b)
    {
    	if(b)
		{
			m_display_mode = 1;
		}
    }


    //--
    void
    Render::radioModeDU(bool b)
    {
    	if(b)
		{
			m_display_mode = 2;
		}
    }


    //--
    void 
    Render::checkboxDiscard(bool b)
    {
    	m_discard = b;

    	if(b && m_displace)
    	{
    		m_displace = false;
    		m_ui_render->checkbox_displace->setChecked(false);
    	}
    }


    //--
    void
    Render::checkboxDisplace(bool b)
    {
    	m_displace = b;

    	if(b && m_discard)
    	{
    		m_discard = false;
    		m_ui_render->checkbox_discard->setChecked(false);
    	}
    }



    //--
    void 
    Render::editDistance(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_distance = value;

    		m_ui_render->edit_distance->setText(QString::number(m_distance));

    		m_sliderguard = true;
    		m_ui_render->slider_dist->setValue(static_cast<int>(m_distance * kDistSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::editTimestep(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_timestep = value;

    		m_ui_render->edit_timestep->setText(QString::number(m_timestep));

    		m_sliderguard = true;
    		m_ui_render->slider_step->setValue(static_cast<int>(m_timestep * kStepSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::editK(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_k = value;

    		m_ui_render->edit_k->setText(QString::number(m_k));

    		m_sliderguard = true;
    		m_ui_render->slider_k->setValue(static_cast<int>(m_k * kKSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::editF(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_f = value;

    		m_ui_render->edit_f->setText(QString::number(m_f));

    		m_sliderguard = true;
    		m_ui_render->slider_f->setValue(static_cast<int>(m_f * kFSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::editDu(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_du = value;

    		m_ui_render->edit_du->setText(QString::number(m_du));

    		m_sliderguard = true;
    		m_ui_render->slider_du->setValue(static_cast<int>(m_du * kDuSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::editDv(const QString& text)
    {
    	bool ok;
    	float value = text.toFloat(&ok);

    	if(ok)
    	{
    		m_dv = value;

    		m_ui_render->edit_dv->setText(QString::number(m_dv));

    		m_sliderguard = true;
    		m_ui_render->slider_dv->setValue(static_cast<int>(m_dv * kDvSliderScale));
    		m_sliderguard = false;
    	}
    }


    //--
    void 
    Render::checkAutomaticTimestep(bool b)
    {
    	m_automatictimestep = b;
    }


    //--
    void 
    Render::sliderEventDu(int size)
    {
    	m_du = static_cast<float>(size) / kDuSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_du->setText(QString::number(m_du));
		}
    }


    //--
    void 
    Render::sliderEventDv(int size)
    {
    	m_dv = static_cast<float>(size) / kDvSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_dv->setText(QString::number(m_dv));
		}
    }


    //--
    void 
    Render::sliderEventK(int size)
    {
    	m_k = static_cast<float>(size) / kKSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_k->setText(QString::number(m_k));
		}
    }
            

    //--
    void 
    Render::sliderEventF(int size)
    {
    	m_f = static_cast<float>(size) / kFSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_f->setText(QString::number(m_f));
		}
    }
            

    //--
    void 
    Render::sliderEventDist(int size)
    {
    	m_distance = static_cast<float>(size) / kDistSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_distance->setText(QString::number(m_distance));
		}
    }
            

    //--
    void 
    Render::sliderEventStep(int size)
    {
    	m_timestep = static_cast<float>(size) / kStepSliderScale;

    	if(!m_sliderguard)
    	{
			m_ui_render->edit_timestep->setText(QString::number(m_timestep));
		}
    }


    //--
    void 
    Render::sliderEventDiscard(int size)
    {
    	m_discard_size = static_cast<float>(size) / kDiscardSliderScale;
    }
            

    //--
    void 
    Render::sliderEventDisplace(int size)
    {
    	m_displace_size = static_cast<float>(size) / kDisplaceSliderScale;
    }


    //--
    void 
    Render::comboEventRender(int idx)
    {
    	m_render_mode = static_cast<RenderMode::Enum>(idx);
    }


    //--
    void 
    Render::mousePressEvent(QMouseEvent* event)
    {
    	QGLWidget::mousePressEvent(event);

    	const Qt::MouseButton button = event->button();

    	if(Qt::LeftButton == button)
    	{
    		m_mouse_position = event->pos();
    		m_mouse_rotation = true;
    	}
    }
        

    //--
   	void 
   	Render::mouseReleaseEvent(QMouseEvent* event)
   	{
   		QGLWidget::mouseReleaseEvent(event);

   		const Qt::MouseButton button = event->button();

   		if(button == Qt::LeftButton)
        {
            m_mouse_rotation = false;
        }
   	}
        

    //--
    void 
    Render::mouseMoveEvent(QMouseEvent* event)
    {
    	QGLWidget::mouseMoveEvent(event);

    	const Qt::MouseButtons buttons = event->buttons();

    	if(m_mouse_rotation)
        {
            const QPointF& mouse_position = event->pos();

            m_rotation_x += static_cast<float>(m_mouse_position.x() - mouse_position.x()) * kMouseRotationScale;
            m_rotation_y += static_cast<float>(m_mouse_position.y() - mouse_position.y()) * kMouseRotationScale;

            m_mouse_position = mouse_position;
        }
    }

}
