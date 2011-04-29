#if !defined(COMP_5201_PROJECT_TABWIDGET_H)
#define COMP_5201_PROJECT_TABWIDGET_H

#include <QtGui/QTabWidget>

namespace Comp5201Project
{
    class TabWidget : public QTabWidget
    {
        Q_OBJECT
        
        public:
            
            TabWidget(QWidget* parent = 0);
            virtual ~TabWidget();

    };
}

#endif //!defined(COMP_5201_PROJECT_TABWIDGET_H)
