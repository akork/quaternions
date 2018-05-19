#include "ode.h"

double Ode::t;
state_type Ode::q;
expression_t Ode::rhs[4];

Ode::Ode(string expr_strings[])
{
  parser_t parser;
  symbol_table_t symbol_table;
  symbol_table.add_variable("t",t);
  symbol_table.add_variable("q0",q[0]);
  symbol_table.add_variable("q1",q[1]);
  symbol_table.add_variable("q2",q[2]);
  symbol_table.add_variable("q3",q[3]);
  symbol_table.add_constants();

  for (int i = 0; i < 4; ++i)
  {
    rhs[i].register_symbol_table(symbol_table);
    parser.compile(expr_strings[i], rhs[i]);
  }
}

void Ode::operator()(const state_type &q, state_type &dxdt, double t)
{
  this->t = t;
  this->q = q;
  qDebug() << t;
  QString str;
  for (int i = 0; i < 4; ++i)
  {
    dxdt[i] = rhs[i].value();
    str += QString::number(dxdt[i]) + "; ";
//    qDebug() << dxdt[i] << "  ";
  }
  qDebug() << str;
}

Odeint_results::Odeint_results()
{}

void Odeint_results::operator()(const state_type &x, double t)
{
  m_states.push_back( x );
  m_times.push_back( t );
  QString str;
  str += "t = " + QString::number(t) + ":  ";
  for (int i = 0; i < 4; ++i)
    str += QString::number(x[i]) + "; ";
  qDebug() << str;
}

state_type Odeint_results::interp(double t)
{
  if (t < m_times[0] || t >= m_times[m_times.size() - 1])
    throw new QException();

  int i = 0;
  while (m_times[i] < t)
    i++;

  double grad;
  state_type ret;
  for (int j = 0; j < 4; ++j)
  {
    grad = (m_states[i][j] - m_states[i-1][j]) / (m_times[i] - m_times[i-1]);
    ret[j] = m_states[i-1][j] + grad * (t - m_times[i-1]);
  }
  return ret;
}

void Odeint_results::clear()
{
  m_states.clear();
  m_times.clear();
}

Odeint_results::operator QString() const {
  QString str;
  for (int i = 0; i < (int) m_states.size(); ++i)
  {
    str += "; t = " + QString::number(m_times[i]) + ":  ";
    for (int j = 0; j < (int) m_states[i].size(); ++j)
    {
      str += QString::number(m_states[i][j]) + "  ";
    }
  }
  return str;
}

std::vector< state_type > Odeint_results::m_states;
std::vector< double > Odeint_results::m_times;
