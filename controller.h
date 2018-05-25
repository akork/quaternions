#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDebug>
#include <QObject>
#include <window.h>
#include <ode.h>
#include "kinematicvariables.h"

class Window;


class Controller : public QObject
{
  Q_OBJECT
public:
  explicit Controller(QObject *parent, Window *window);
  ~Controller() {
    qDebug() << "controller destroyed";
  }

signals:
  void state_changed(KinematicVariables vars);

public slots:
  void ode_integrate();
  void parse_parameters();
  void timer_restart();
  void animation();
  void integrate_and_start();
  void reset_ic();


private:
  Window * window;
  double t;
  double tend;
  double step;
  string omega[3];
  string expr_strings[4];
  Ode * ode;
  Odeint_results odeint_results;
  QBasicTimer timer;
  state_type ic;
  void timerEvent(QTimerEvent *);
  bool timerPaused;
  float alpha, beta, gamma;
};

#endif // CONTROLLER_H
