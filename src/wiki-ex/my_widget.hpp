#pragma once

#include <QWidget>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
  public:
    MyWidget(const uint32_t window_width, const uint32_t window_height)
      : m_initial_window_height(window_height), m_initial_window_width(window_width)
    {
        this->setFixedSize(window_width, window_height);

        m_buttonInfo = new QPushButton("Info", this);
        m_buttonInfo->setGeometry(window_width / 2 - 50, 50, 100, 50);

        m_buttonQuit = new QPushButton("Quit", this);
        m_buttonQuit->setGeometry(window_width / 2 - 110, window_height - 160, 220, 110);

        // Relaying
        const auto c1 =
          QObject::connect(m_buttonInfo, SIGNAL(clicked()), this, SIGNAL(displayInfo()));
        const auto c2 =
          QObject::connect(m_buttonQuit, SIGNAL(clicked()), this, SIGNAL(requestQuit()));

        this->show();
    }

  signals:
    void requestQuit();
    void displayInfo();

  private:
    const uint32_t m_initial_window_height;
    const uint32_t m_initial_window_width;
    QPushButton *m_buttonQuit;
    QPushButton *m_buttonInfo;
};