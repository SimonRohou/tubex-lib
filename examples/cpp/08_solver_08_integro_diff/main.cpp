#include "ibex.h"
#include "tubex.h"
#include "tubex-solver.h"

using namespace std;
using namespace ibex;
using namespace tubex;

class FncIntegroDiff : public tubex::Fnc
{
  public: 

    FncIntegroDiff() : Fnc(1,1) {};
    
    const TubeVector eval(const TubeVector& x) const
    {
      return Fnc::eval(x);
    }

    const IntervalVector eval(const Interval& t, const TubeVector& x) const
    {
      return IntervalVector(x.dim(), 1.) - 2. * x[t] - 5. * x.integral(t);
    }
};

void contract(TubeVector& x)
{
  // Boundary constraints

    Variable vx0, vx1;
    SystemFactory fac;
    fac.add_var(vx0);
    fac.add_var(vx1);
    fac.add_ctr(sqr(vx0) + sqr(vx1) = 1);
    System sys(fac);
    ibex::CtcHC4 hc4(sys);
    IntervalVector bounds(2);
    bounds[0] = x[0.][0];
    bounds[1] = x[1.][0];
    hc4.contract(bounds);
    x.set(IntervalVector(1,bounds[0]), 0.);
    x.set(IntervalVector(1,bounds[1]), 1.);

  FncIntegroDiff f;

  CtcPicard ctc_picard(true, 1.1);
  ctc_picard.contract(f, x, FORWARD | BACKWARD);

  CtcDeriv ctc_deriv(true);
  ctc_deriv.contract(x, IntervalVector(x.dim(), 1.) - 2.*x - 5.*x.primitive(), FORWARD | BACKWARD);
}

int main()
{
  /* =========== PARAMETERS =========== */

    int n = 1;
    Vector epsilon(n, 0.1);
    Interval domain(0.,1.);
    TubeVector x(domain, n);
    Trajectory truth1(domain, tubex::Function("0.5*exp(-t)*(-1.78315*cos(2*t)+1.89158*sin(2*t))"));
    Trajectory truth2(domain, tubex::Function("0.5*exp(-t)*(1.97753*cos(2*t)+0.0112371*sin(2*t))"));

  /* =========== SOLVER =========== */

    tubex::Solver solver(epsilon, 0.01, 0.1, 0.1);
    solver.figure()->add_trajectory(&truth1, "truth", "blue");
    solver.figure()->add_trajectory(&truth2, "truth", "red");
    list<TubeVector> l_solutions = solver.solve(x, &contract);


  // Checking if this example is still working:
  return (solver.solution_encloses(l_solutions, truth1)
       && solver.solution_encloses(l_solutions, truth2)) ? EXIT_SUCCESS : EXIT_FAILURE;
}