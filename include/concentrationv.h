/*
 *  concentrationv.h
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

#if !defined(COMP_5201_PROJECT_CONCENTRATIONV_H)
#define COMP_5201_PROJECT_CONCENTRATIONV_H

#include <QtGui/QWidget>

#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtCore/QPoint>

class QMouseEvent;
class QPaintEvent;
class QResizeEvent;

class QDockWidget;

namespace Ui
{
    class concentrationv;
}

namespace Comp5201Project
{
    class Window;

    class ConcentrationV : public QWidget
    {
        Q_OBJECT

        friend class Window;
        
        public:
            
            ConcentrationV(QWidget* parent = 0);
            virtual ~ConcentrationV();

        public slots:

            void sliderEventSize(int size);
            void sliderEventConcentration(int concentration);
            void sliderEventBaseConcentration(int concentration);

            void buttonDefaults();
            void buttonClear();
            void buttonSave();
            void buttonLoad();
            void buttonInvert();
            void buttonRandom();

        public:

        	void clearConcentration();

            void requestDock(Window* window, QDockWidget* dock);

            void concentration(QImage& img);

        protected:
     
     		void mousePressEvent(QMouseEvent* event);
     		void mouseMoveEvent(QMouseEvent* event);
     		void mouseReleaseEvent(QMouseEvent* event);
     		void paintEvent(QPaintEvent* event);
     		void resizeEvent(QResizeEvent* event);

     	protected:

     		void drawLineTo(const QPoint& end_point);
     		void resizeImage(QImage* image, const QSize& new_size);

            void createSettings();

        protected:

            Window* m_parent;

        	int m_pen_width;
            int m_concentration;
            int m_backgroundconcentration;

            bool m_drawing;

        	QImage m_image;
        	QPoint m_last_point;
        	QColor m_pen_color;

            QWidget* m_settings;
            Ui::concentrationv* m_ui_concentration;
    };
}

#endif //!defined(COMP_5201_PROJECT_CONCENTRATIONV_H)
