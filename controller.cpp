#include "controller.h"

Controller::Controller(QObject *parent, Window *window) : QObject(parent)
{
  this->window = window;
  integrate_and_start();
}

void Controller::ode_integrate()
{
  parse_parameters();
  ode = new Ode(expr_strings);
  runge_kutta4<state_type> stepper;
//  state_type x = {{ 1.0 , 0.0 , 0.0, 0.0 }}; // initial conditions
  odeint_results.clear();
  integrate_const(stepper, *ode, ic, 0.0, tend + step, step, odeint_results);
}

void Controller::parse_parameters()
{
  omega[0] = window->omegaTable->item(0, 1)->text().toUtf8().constData();
  omega[1] = window->omegaTable->item(1, 1)->text().toUtf8().constData();
  omega[2] = window->omegaTable->item(2, 1)->text().toUtf8().constData();
  expr_strings[0] = string("") + "-0.5*(" +
      "(" + omega[0] + ")*q1+" +
      "(" + omega[1] + ")*q2+" +
      "(" + omega[2] + ")*q3)";
  expr_strings[1] = string("") + "0.5*(" +
      "(" + omega[0] + ")*q0+" +
      "(" + omega[1] + ")*q3-" +
      "(" + omega[2] + ")*q2)";
  expr_strings[2] = string("") + "0.5*(" +
      "(" + omega[1] + ")*q0+" +
      "(" + omega[2] + ")*q1-" +
      "(" + omega[0] + ")*q3)";
  expr_strings[3] = string("") + "0.5*(" +
      "(" + omega[2] + ")*q0+" +
      "(" + omega[0] + ")*q2-" +
      "(" + omega[1] + ")*q1)";
  tend = window->omegaTable->item(3, 1)->text().toDouble();
  step = window->omegaTable->item(4, 1)->text().toDouble();
  ic = {{
          window->quaternTable->item(0, 1)->text().toDouble(),
          window->quaternTable->item(1, 1)->text().toDouble(),
          window->quaternTable->item(2, 1)->text().toDouble(),
          window->quaternTable->item(3, 1)->text().toDouble(),
        }};

//  alpha =  window->eulerTable->item(0, 1)->text().toDouble() * M_PI / 180;
//  beta =  window->eulerTable->item(1, 1)->text().toDouble() * M_PI / 180;
//  gamma =  window->eulerTable->item(2, 1)->text().toDouble() * M_PI / 180;
//      auto q = Quaternion::fromEulerAngles(alpha, beta, gamma);
//      ic[0] = q.getW();
//      ic[1] = q.getX();
//      ic[2] = q.getY();
//      ic[3] = q.getZ();
}

void Controller::timer_restart()
{
  t = 0;
  timer.stop();
  timer.start(20, this);
  timerPaused = false;
}

void Controller::animation()
{
  if (timer.isActive()) {
    timerPaused = true;
    timer.stop();
  } else {
    if (timerPaused)
    {
      timer.start(20, this);
    } else {
      timer_restart();
    }
  }
}

void Controller::integrate_and_start()
{
  ode_integrate();
  timer_restart();
}

void Controller::reset_ic()
{
  timer.stop();
    window->quaternTable->setItem(0, 1, new QTableWidgetItem("1"));
    window->quaternTable->setItem(1, 1, new QTableWidgetItem("0"));
    window->quaternTable->setItem(2, 1, new QTableWidgetItem("0"));
    window->quaternTable->setItem(3, 1, new QTableWidgetItem("0"));

    window->eulerTable->setItem(0, 1, new QTableWidgetItem("0"));
    window->eulerTable->setItem(1, 1, new QTableWidgetItem("0"));
    window->eulerTable->setItem(2, 1, new QTableWidgetItem("0"));

    parse_parameters();
    state_type q = ic;
    auto eulerAngles = QQuaternion(q[0], q[1], q[2], q[3]).normalized().toEulerAngles();
    auto vars = KinematicVariables {
        q[0],
        q[1],
        q[2],
        q[3],
        eulerAngles.x(),
        eulerAngles.y(),
        eulerAngles.z(),
        t
    };
    emit state_changed(vars);
}

void Controller::timerEvent(QTimerEvent *)
{
    t += 0.02;
    if (t >= tend) { timer.stop(); timerPaused = false; return; }
    state_type q = odeint_results.interp(t);
    auto eulerAngles = QQuaternion(q[0], q[1], q[2], q[3]).normalized().toEulerAngles();
    auto vars = KinematicVariables {
        q[0],
        q[1],
        q[2],
        q[3],
        eulerAngles.x(),
        eulerAngles.y(),
        eulerAngles.z(),
        t
    };
    emit state_changed(vars);

//window->mainWidget->setModelRotation(quaternion);
//window->updateVariables(quaternion);
//objects[0]->setRotation(rotation);
//objects[1]->setRotation(rotation);
//needToUpdate = true;

}
