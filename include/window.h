/*
 *  window.h
 *  Gray-Scott Reaction Diffusion system.
 *
 *  Main window.
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

#if !defined(COMP_5201_PROJECT_WINDOW_H)
#define COMP_5201_PROJECT_WINDOW_H

#include <QtGui/QMainWindow>

class QDockWidget;
class QTabWidget;

namespace Comp5201Project
{
    class TabWidget;

    class ConcentrationU;
    class ConcentrationV;
    class Render;

    class Window : public QMainWindow
    {
        Q_OBJECT
        
        public:
            
            Window(QWidget* parent = 0, Qt::WindowFlags flags = 0);
            virtual ~Window();

        public:

            void setDock(QDockWidget* widget);

        public slots:

            void tabChanged(int idx);


        protected:

            void createTabs();
            void createDocks();

        protected:

            QTabWidget* m_tabs;

            ConcentrationU* m_tab_concentrationu;
            ConcentrationV* m_tab_concentrationv;
            Render* m_tab_render;

            QDockWidget* m_dock_concentrationu;
            QDockWidget* m_dock_concentrationv;
            QDockWidget* m_dock_render;
    };
}

#endif //!defined(COMP_5201_PROJECT_WINDOW_H)
