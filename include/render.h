/*
 *  render.h
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

#if !defined(COMP_5201_PROJECT_RENDER_H)
#define COMP_5201_PROJECT_RENDER_H

#include <QtCore/QtGlobal>

#if defined(Q_OS_WIN)
	#include <GL/glew.h>
#endif

#include <QtOpenGL/QGLWidget>

namespace Ui
{
    class render;
}

class QDockWidget;

class QMouseEvent;

class QTime;
class QTimer;

class QGLShaderProgram;

namespace Comp5201Project
{
	class Window;
	class FrameBuffer;

    namespace RenderMode
    {
        enum Enum
        {
            Render2d        = 0,
            Render3dSphere  = 1,
            Render3dTorus   = 2,
            Render3dTeapot  = 3
        };
    }

    class Render : public QGLWidget
    {
        Q_OBJECT
        
        public:
            
            Render(QWidget* parent = 0);
            Render(const QGLFormat& gl_format, QWidget* parent = 0);
            virtual ~Render();

        public slots:

        	void buttonStart();
        	void buttonRestart();
        	void buttonDefaults();

            void buttonSaveImage();

            void buttonSaveConfig();
            void buttonLoadConfig();

        	void radioModeU(bool b);
        	void radioModeV(bool b);
        	void radioModeDU(bool b);

            void checkboxDiscard(bool b);
            void checkboxDisplace(bool b);

        	void checkAutomaticTimestep(bool b);

        	void editDistance(const QString& text);
        	void editTimestep(const QString& text);

        	void editF(const QString& text);
        	void editK(const QString& text);

        	void editDu(const QString& text);
        	void editDv(const QString& text);

            void sliderEventDu(int size);
            void sliderEventDv(int size);
            void sliderEventK(int size);
            void sliderEventF(int size);
            void sliderEventDist(int size);
            void sliderEventStep(int size);

            void sliderEventDiscard(int size);
            void sliderEventDisplace(int size);

            void comboEventRender(int idx);

        public:

        	void requestDock(Window* window, QDockWidget* dock);
        	void update();

        public:

        	void setConcentrationMapU(const QImage& img);
        	void setConcentrationMapV(const QImage& img);

        protected:

        	void initializeGL();
        	void paintGL();
        	void resizeGL(int width, int height);

       	protected:

            void mousePressEvent(QMouseEvent* event);
            void mouseReleaseEvent(QMouseEvent* event);
            void mouseMoveEvent(QMouseEvent* event);    

        protected:

        	void createSettings();
        	void createShaders();
        	void createFBOs();


        protected:

        	Window* m_parent;

            bool m_sliderguard;
        	bool m_initialized;
        	bool m_started;
            bool m_paused;
            bool m_resized;
        	int m_frame_id;
        	float m_frame_delta;
        	float m_total_time;

        	int m_width;
        	int m_height;

        	QTime* m_time_frame;
        	QTimer* m_timer_scene_update;

        	QWidget* m_settings;
            Ui::render* m_ui_render;

            QGLShaderProgram* m_shader_greyscott;
            QGLShaderProgram* m_shader_render2d;
            QGLShaderProgram* m_shader_render3d;

            FrameBuffer* m_fbo_greyscottresult;
            FrameBuffer* m_fbo_greyscottresult2;

            QImage m_concentration_u;
            QImage m_concentration_v;

            GLuint m_tex_initial_concentration;

            int m_display_mode;
            float m_distance;
            float m_timestep;
            bool m_automatictimestep;
            float m_k;
            float m_f;
            float m_du;
            float m_dv;

            RenderMode::Enum m_render_mode;

            QPointF m_mouse_position;
            bool m_mouse_rotation;

            float m_rotation_x;
            float m_rotation_y;

            bool m_discard;
            bool m_displace;

            float m_discard_size;
            float m_displace_size;
    };
}

#endif //!defined(COMP_5201_PROJECT_RENDER_H)
