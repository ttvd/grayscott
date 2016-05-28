/*
 *  window.cpp
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

#include <window.h>
#include <tabwidget.h>

#include <concentrationv.h>
#include <concentrationu.h>
#include <render.h>

#include <QDockWidget>
#include <QTabWidget>
#include <QSizePolicy>

#include <QGLFormat>

namespace Comp5201Project
{
	//--
    Window::Window(QWidget* parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    m_tab_concentrationu(0),
    m_tab_concentrationv(0),
    m_tab_render(0)
    {
    	createTabs();
    	createDocks();

        setWindowTitle(tr("Comp 5201 Project - Diffusion Reaction"));
        resize(800, 600);
    }


    //--
    Window::~Window()
    {
        
    }


    //--
    void
    Window::createTabs()
    {
    	m_tabs = new QTabWidget(this);

    	m_tab_concentrationu = new ConcentrationU(m_tabs);
    	m_tabs->addTab(m_tab_concentrationu, tr("Concentration U"));

    	m_tab_concentrationv = new ConcentrationV(m_tabs);
    	m_tabs->addTab(m_tab_concentrationv, tr("Concentration V"));

        // [rad] We need to specify GL options before constructing GL widget.
        #if defined(Q_OS_WIN)

            QGLFormat gl_format = QGLFormat::defaultFormat();
            gl_format.setSampleBuffers(true);
            gl_format.setSamples(4);

            m_tab_render = new Render(gl_format, m_tabs);
        #else

            m_tab_render = new Render(m_tabs);

        #endif

        m_tabs->addTab(m_tab_render, tr("Simulation Render"));
    	

    	QObject::connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    	setCentralWidget(m_tabs);
    }


    //--
    void 
    Window::tabChanged(int idx)
    {
    	m_dock_concentrationv->setVisible(false);
    	m_dock_concentrationu->setVisible(false);
    	m_dock_render->setVisible(false);

    	switch(idx)
    	{
    		case 0:
    			{
    				m_dock_concentrationu->setVisible(true);
    			}
    			break;

    		case 1:
    			{
    				m_dock_concentrationv->setVisible(true);
    			}
    			break;

    		case 2:
    			{
    				QImage concentration_u;
    				m_tab_concentrationu->concentration(concentration_u);

                    QImage concentration_v;
    				m_tab_concentrationv->concentration(concentration_v);

    				m_tab_render->setConcentrationMapU(concentration_u);
    				m_tab_render->setConcentrationMapV(concentration_v);

    				m_dock_render->setVisible(true);
    			}
    			break;
    	}
    }


    //--
    void
    Window::createDocks()
    {
    	// [rad] ConcentrationU tab settings.
    	m_dock_concentrationu = new QDockWidget("U Concentration Options");
    	m_dock_concentrationu->setAllowedAreas(Qt::LeftDockWidgetArea);
    	m_dock_concentrationu->setFixedSize(QSize(250, 600));
    	m_dock_concentrationu->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    	m_tab_concentrationu->requestDock(this, m_dock_concentrationu);
    	m_dock_concentrationu->setStyleSheet("QDockWidget::title {text-align: Center;}");
    	m_dock_concentrationu->setFeatures(QDockWidget::NoDockWidgetFeatures);

    	// [rad] ConcentrationV tab settings.
    	m_dock_concentrationv = new QDockWidget("V Concentration Options");
    	m_dock_concentrationv->setAllowedAreas(Qt::LeftDockWidgetArea);
    	m_dock_concentrationv->setFixedSize(QSize(250, 600));
    	m_dock_concentrationv->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    	m_tab_concentrationv->requestDock(this, m_dock_concentrationv);
    	m_dock_concentrationv->setStyleSheet("QDockWidget::title {text-align: Center;}");
    	m_dock_concentrationv->setFeatures(QDockWidget::NoDockWidgetFeatures);

    	// [rad] Render tab settings.
    	m_dock_render = new QDockWidget("Simulation Render");
    	m_dock_render->setAllowedAreas(Qt::LeftDockWidgetArea);
    	m_dock_render->setFixedSize(QSize(250, 600));
    	m_dock_render->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    	m_tab_render->requestDock(this, m_dock_render);
    	m_dock_render->setStyleSheet("QDockWidget::title {text-align: Center;}");
    	m_dock_render->setFeatures(QDockWidget::NoDockWidgetFeatures);

    	// [rad] Make first tab - concentration u.
		m_dock_concentrationu->setVisible(true);
		addDockWidget(Qt::LeftDockWidgetArea, m_dock_concentrationu);

		m_dock_concentrationv->setVisible(false);
		addDockWidget(Qt::LeftDockWidgetArea, m_dock_concentrationv);

		m_dock_render->setVisible(false);
		addDockWidget(Qt::LeftDockWidgetArea, m_dock_render);
    }
}
