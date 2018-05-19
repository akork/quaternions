#ifndef ODE_H
#define ODE_H

#include "exprtk/exprtk.hpp"
#include <boost/numeric/odeint.hpp>
#include <QString>
#include <QDebug>
#include <QException>

using namespace std;
using namespace boost::numeric::odeint;

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;

typedef boost::array< double , 4 > state_type;

class Ode
{
public:
  Ode(string expr_strings[4]);
  void operator() (const state_type &q , state_type &dxdt , double t);
private:
  static double t;
  static state_type q;
  static expression_t rhs[4];
};

struct Odeint_results
{
public:
    Odeint_results();

    void operator()( const state_type &x , double t );
    operator QString() const;
    state_type interp(double t);
    void clear();

private:
    static std::vector< state_type > m_states;
    static std::vector< double > m_times;

};

#endif // ODE_H
