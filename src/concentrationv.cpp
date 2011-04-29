/*
 *  concentrationv.cpp
 *  Gray-Scott Reaction Diffusion system.
 *
 *  Concentration V Qt tab.
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

#include <concentrationv.h>
#include <window.h>

#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>

#include <QtGui/QPainter>
#include <QtGui/QDockWidget>
#include <QtGui/QFileDialog>

#include <QtCore/QDebug>

#include <ctime>

#include "ui_concentrationv.h"

namespace Comp5201Project
{
	//--
	static const int kDefaultPenSize = 50;
	static const int kDefaultPenConcentration = 0;
	static const int kDefaultBaseConcentration = 255;

	static const int kMaxPenSize = 255;
	static const int kMaxConcentration = 255;


	//--
	ConcentrationV::ConcentrationV(QWidget* parent) :
	QWidget(parent),
	m_pen_width(kDefaultPenSize),
	m_concentration(kDefaultPenConcentration),
	m_backgroundconcentration(kDefaultBaseConcentration),
	m_drawing(false)
	{
		m_parent = static_cast<Window*>(parent);

		// [rad] Fix resizing.
		setAttribute(Qt::WA_StaticContents);

		createSettings();

        resizeEvent(0);
	}	


	//--
	ConcentrationV::~ConcentrationV()
	{
		if(m_ui_concentration)
		{
			delete(m_ui_concentration);
		}
	}


	//--
	void
	ConcentrationV::mousePressEvent(QMouseEvent* event)
	{
		if(Qt::LeftButton == event->button())
		{
			m_last_point = event->pos();
			m_drawing = true;
		}
	}


	//--
	void
	ConcentrationV::mouseMoveEvent(QMouseEvent* event)
	{
		if((event->buttons() & Qt::LeftButton) && m_drawing)
		{
        	drawLineTo(event->pos());
        }
	}


	//--
	void 
	ConcentrationV::mouseReleaseEvent(QMouseEvent* event)
 	{
    	if(event->button() == Qt::LeftButton && m_drawing) 
    	{
    		drawLineTo(event->pos());
    		m_drawing = false;
    	}
    }


    //--
    void 
    ConcentrationV::paintEvent(QPaintEvent* event)
 	{
    	QPainter painter(this);
    	painter.setRenderHints(QPainter::Antialiasing);

     	QRect dirtyRect = event->rect();
     	painter.drawImage(dirtyRect, m_image, dirtyRect);
	}


	//--
	void 
	ConcentrationV::drawLineTo(const QPoint& end_point)
	{
		QPainter painter(&m_image);
		painter.setRenderHints(QPainter::Antialiasing);

		QColor pen_color(m_concentration, m_concentration, m_concentration);

		painter.setPen(QPen(pen_color, m_pen_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.drawLine(m_last_point, end_point);

		int rad = (m_pen_width / 2) + 2;

		update(QRect(m_last_point, end_point).normalized().adjusted(-rad, -rad, rad, rad));

		m_last_point = end_point;
	}


	//--
	void 
	ConcentrationV::resizeEvent(QResizeEvent* event)
	{
     	resizeImage(&m_image, QSize(width(), height()));
        update();

        if(!event)
        {
            return;
        }
     
     	QWidget::resizeEvent(event);
	}


	//--
	void 
	ConcentrationV::resizeImage(QImage* image, const QSize& new_size)
	{
		if(image->size() == new_size)
        {
	        return;
	    }

	    QImage new_image(new_size, QImage::Format_ARGB32);
     	new_image.fill(qRgb(m_backgroundconcentration, m_backgroundconcentration, m_backgroundconcentration));

     	QPainter painter(&new_image);
     	painter.drawImage(QPoint(0, 0), *image);
     	*image = new_image;
	}


	//--
	void
	ConcentrationV::clearConcentration()
	{
		m_image.fill(qRgb(m_backgroundconcentration, m_backgroundconcentration, m_backgroundconcentration));
		update();
	}


	//--
	void 
	ConcentrationV::createSettings()
	{
		m_settings = new QWidget();
		m_ui_concentration = new Ui::concentrationv();
		m_ui_concentration->setupUi(m_settings);

		m_ui_concentration->slider_size->setRange(0, kMaxPenSize);
		m_ui_concentration->slider_size->setValue(kDefaultPenSize);
		QObject::connect(m_ui_concentration->slider_size, SIGNAL(valueChanged(int)), this, SLOT(sliderEventSize(int)));

		m_ui_concentration->slider_concentration->setRange(0, kMaxConcentration);
		m_ui_concentration->slider_concentration->setValue(kDefaultPenConcentration);
		QObject::connect(m_ui_concentration->slider_concentration, SIGNAL(valueChanged(int)), this, SLOT(sliderEventConcentration(int)));		
	
		m_ui_concentration->slider_backgroundconcentration->setRange(0, kMaxConcentration);
		m_ui_concentration->slider_backgroundconcentration->setValue(kDefaultBaseConcentration);
		QObject::connect(m_ui_concentration->slider_backgroundconcentration, SIGNAL(valueChanged(int)), this, SLOT(sliderEventBaseConcentration(int)));		
	

		QObject::connect(m_ui_concentration->button_clear, SIGNAL(clicked()), this, SLOT(buttonClear()));
		QObject::connect(m_ui_concentration->button_defaults, SIGNAL(clicked()), this, SLOT(buttonDefaults()));
		QObject::connect(m_ui_concentration->button_load, SIGNAL(clicked()), this, SLOT(buttonLoad()));
		QObject::connect(m_ui_concentration->button_save, SIGNAL(clicked()), this, SLOT(buttonSave()));
		QObject::connect(m_ui_concentration->button_invert, SIGNAL(clicked()), this, SLOT(buttonInvert()));
		QObject::connect(m_ui_concentration->button_random, SIGNAL(clicked()), this, SLOT(buttonRandom()));
	}


	//--
	void 
	ConcentrationV::requestDock(Window* window, QDockWidget* dock)
	{
        Q_UNUSED(window);
		dock->setWidget(m_settings);
	}


	//--
	void 
	ConcentrationV::sliderEventSize(int size)
	{
		m_pen_width = size;
		m_ui_concentration->label_size->setText(QString("Brush size: ") + QString::number(size));
	}


	//--
    void
    ConcentrationV::sliderEventConcentration(int c)
    {
    	m_concentration = c;
    	m_ui_concentration->label_concentration->setText(QString("Brush concentration: ") + QString::number(c));
    }


    //--
    void
    ConcentrationV::sliderEventBaseConcentration(int c)
    {
    	m_backgroundconcentration = c;
    	m_ui_concentration->label_backgroundconcentration->setText(QString("Background concentration: ") + QString::number(c));
    }


    //--
    void
    ConcentrationV::buttonDefaults()
    {
    	sliderEventSize(kDefaultPenSize);
    	sliderEventConcentration(kDefaultPenConcentration);
    	sliderEventBaseConcentration(kDefaultBaseConcentration);

    	m_ui_concentration->slider_concentration->setValue(kDefaultPenConcentration);
    	m_ui_concentration->slider_backgroundconcentration->setValue(kDefaultBaseConcentration);
    	m_ui_concentration->slider_size->setValue(kDefaultPenSize);

    }


    //--
    void
    ConcentrationV::buttonClear()
    {
    	m_image.fill(qRgb(m_backgroundconcentration, m_backgroundconcentration, m_backgroundconcentration));
     	update();
    }


    //--
    void
    ConcentrationV::buttonLoad()
    {
    	QString filename = QFileDialog::getOpenFileName(this, tr("Open concentration file"), "", tr("Concentration images (*.bmp *.png *.jpg *.jpeg *.tiff)"));
    
    	QImage loaded_image;

    	if(!loaded_image.load(filename))
    	{
    		return;
    	}

    	QSize new_size = loaded_image.size().expandedTo(size());
     	resizeImage(&loaded_image, new_size);
     	
     	// [rad] Need to convert to grayscale.
     	m_image = loaded_image;

     	for(int x = 0; x < m_image.width(); ++x)
     	{
     		for(int y = 0; y < m_image.height(); ++y)
     		{
     			int pixel = m_image.pixel(x, y);
     			int gray = qGray(pixel);
     			//int alpha = qAlpha(pixel);

     			m_image.setPixel(x, y, qRgb(gray, gray, gray));
     		}
     	}

     	update();
	}


    //--
    void
    ConcentrationV::buttonSave()
    {
    	QString filename = QFileDialog::getSaveFileName(this, "Save concentration file", "", tr("Concentration images (*.bmp *.png *.jpg *.jpeg *.tiff)"));

    	QImage visible_image = m_image;
    	resizeImage(&visible_image, size());

     	if(visible_image.save(filename))
     	{
     		qDebug() << "Failed saving image.";
     	}
    }


    //--
    void
    ConcentrationV::buttonInvert()
    {
    	m_image.invertPixels(QImage::InvertRgb);
    	
    	update();
    }


    //--
    void
    ConcentrationV::buttonRandom()
    {
    	qsrand(time(0));

        // [rad] Create buffer.
        int** buffer = new int*[m_image.width()];
        
        for(int idx = 0; idx < m_image.width(); ++idx)
        {
            buffer[idx] = new int[m_image.height()];
        }


        for(int x = 0; x < m_image.width(); ++x)
        {
            for(int y = 0; y < m_image.height(); ++y)
            {
                buffer[x][y] = 0.02837f;
            }
        }

        
        for(int idx = 0; idx < 100; ++idx)
        {
            int side = 25 + (rand() % 50);

            int pos_x = rand() % m_image.width();
            int pos_y = rand() % m_image.height();

            int conc_v = rand() % 256;

            for(int side_x = 0; side_x < side; ++side_x)
            {
                if(side_x  + pos_x >= m_image.width())
                {
                    break;
                }

                for(int side_y = 0; side_y < side; ++side_y)
                {
                    if(side_y  + pos_y >= m_image.height())
                    {
                        break;
                    }

                    buffer[side_x + pos_x][side_y + pos_y] = conc_v;
                }
            }
        }

        for(int x = 0; x < m_image.width(); ++x)
        {
            for(int y = 0; y < m_image.height(); ++y)
            {
                m_image.setPixel(x, y, qRgb(buffer[x][y], buffer[x][y], buffer[x][y]));
            }
        }
        

        for(int idx = 0; idx < m_image.width(); ++idx)
        {
            delete[](buffer[idx]);
        }

        delete[](buffer);

     	update();
    }


    //--
    void 
    ConcentrationV::concentration(QImage& img)
    {
    	img = m_image;
    }
}
