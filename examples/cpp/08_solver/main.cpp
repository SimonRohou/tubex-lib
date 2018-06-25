#include "tubex.h"
#include <time.h>

using namespace std;
using namespace ibex;
using namespace tubex;

#define IVP 1
#define BVP 2
#define DAE 3
#define IVP_PICARD 4
#define BVP_CP2010 5
#define DELAY 6
#define SOLVER_TEST BVP

#if SOLVER_TEST == IVP

  void contract(TubeVector& x)
  {
    Function f("x", "-sin(x)");

    if(x.codomain().is_unbounded())
    {
      tubex::CtcPicard ctc_picard;
      ctc_picard.contract(f, x);
    }

    CtcDeriv ctc_deriv;
    ctc_deriv.contract(x, TubeVector(f, x));
  }

#elif SOLVER_TEST == IVP_PICARD

  void contract(TubeVector& x)
  {
    Function f("x", "-x");

    if(x.codomain().is_unbounded())
    {
      tubex::CtcPicard ctc_picard;
      ctc_picard.contract(f, x);
    }

    CtcDeriv ctc_deriv;
    ctc_deriv.contract(x, TubeVector(f, x));
  }

#elif SOLVER_TEST == DAE

  void contract(TubeVector& x)
  {
    //Variable vx, vy;
    //Function f("x", "y", "(y, [-oo,oo])");//vx, vy, Return(vy,"[-oo,oo]"));

    //if(x.codomain().is_unbounded())
    //{
    //  tubex::CtcPicard ctc_picard;
    //  ctc_picard.contract(f, x);
    //}

    Variable vx0, vx1;
    SystemFactory fac;
    fac.add_var(vx0);
    fac.add_var(vx1);
    fac.add_ctr(sqr(vx0) + sqr(vx1) = 1);
    System sys(fac);
    ibex::CtcHC4 hc4(sys);
    tubex::CtcHC4 ctc_hc4;
    ctc_hc4.contract(hc4, x);

    TubeVector xdot(x);
    TubeSlice *xdot_slice = xdot.getFirstSlice(), *x_slice = x.getFirstSlice();
    while(xdot_slice != NULL)
    {
      IntervalVector box(2);
      box[0] = x_slice->inputGate()[1];
      xdot_slice->setInputGate(box);
      box[0] = x_slice->outputGate()[1];
      xdot_slice->setOutputGate(box);
      box[0] = x_slice->codomain()[1];
      xdot_slice->setEnvelope(box);

      x_slice = x_slice->nextSlice();
      xdot_slice = xdot_slice->nextSlice();
    }

    CtcDeriv ctc_deriv;
    ctc_deriv.contract(x, xdot);
  }

#elif SOLVER_TEST == BVP
      
  void contract(TubeVector& x)
  {
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
    
    Function f("x", "x");

    if(x.codomain().is_unbounded())
    {
      tubex::CtcPicard ctc_picard;
      ctc_picard.contract(f, x, true);
    }
    
    CtcDeriv ctc_deriv;
    ctc_deriv.contract(x, TubeVector(f, x));
  }

#elif SOLVER_TEST == BVP_CP2010
      
  void contract(TubeVector& x)
  {
    Variable x1, x2;
    Function f(x1, x2, Return(x2, 0.05 * x1 * exp((20.*0.4*(1.-x1)) / (1. + 0.4 * (1.-x1)))));

    if(x.codomain().is_unbounded())
    {
      cout << "starting Picard " << x.nbSlices() << endl;
      tubex::CtcPicard ctc_picard;
      ctc_picard.contract(f, x);
      cout << "ending Picard" << endl;
    }
    
    CtcDeriv ctc_deriv;
    ctc_deriv.contract(x, TubeVector(f, x));
  }

#elif SOLVER_TEST == DELAY
      
  void contract(TubeVector& x)
  {
    float a = 0.5;

    /*if(v_x[0].codomain().is_unbounded())
    {
      tubex::CtcPicard ctc_picard;
      Function f("x", "exp(0.5)*x(t-0.5)");
      ctc_picard.contract(f, v_x[0]);
    }*/

    //CtcDelay tube_delay;
    //Interval intv_a(a);
    //tube_delay.contract(intv_a, v_x[1], v_x[0]);
    //v_x[2] &= v_x[1] * exp(intv_a);
    //v_x[1] &= v_x[2] * log(intv_a);
    //
    //v_x[0].ctcFwdBwd(v_x[2]);
  }

#endif


int main(int argc, char *argv[])
{
  /* =========== PARAMETERS =========== */

    #if SOLVER_TEST == IVP

      float epsilon = 0.1;
      Interval domain(0.,10.);
      TubeVector x(domain, 1);
      x.set(IntervalVector(1,1.), 0.); // initial condition
      bool show_details = true;

    #elif SOLVER_TEST == IVP_PICARD

      float epsilon = 0.05;
      Interval domain(0.,1.);
      TubeVector x(domain, 1);
      x.set(IntervalVector(1, 1.), 0.); // initial condition
      bool show_details = true;

    #elif SOLVER_TEST == DAE

      float epsilon = 0.5;
      Interval domain(0.,1.);
      TubeVector x(domain, IntervalVector(2, Interval(-1.,1.)));
      bool show_details = true;

    #elif SOLVER_TEST == BVP

      float epsilon = 0.05;
      Interval domain(0.,1.);
      TubeVector x(domain, 1);
      bool show_details = true;

    #elif SOLVER_TEST == BVP_CP2010

      float epsilon = 0.1;
      Interval domain(0.,1.);
      IntervalVector box(2), x0(2), xf(2);

      //box[0] = Interval(0.,1.);
      //box[1] = Interval(0.,2.);
      TubeVector x(domain, box);

      x0[0] = Interval(0.,1.); x0[1] = 0.;
      xf[0] = 1.;
      x.set(x0, 0.);
      x.set(xf, 1.);
      bool show_details = true;

    #elif SOLVER_TEST == DELAY

      //Interval domain(0.,10.);
      //float epsilon = 0.2;
      //v.push_back(Tube(domain, exp(domain)));
      //v.push_back(Tube(domain));
      //v.push_back(Tube(domain));
      //bool show_details = true;

    #endif

  /* =========== SOLVER =========== */

    tubex::Solver solver;
    clock_t tStart = clock();
    vector<TubeVector> v_solutions = solver.solve(x, &contract, epsilon);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    if(v_solutions.size() == 0)
      cout << "no solution found" << endl;

  /* =========== GRAPHICS =========== */

    vibes::beginDrawing();
    VibesFigure_Tube fig("Solver", x.dim());

    #if SOLVER_TEST == IVP

      fig.setProperties(100,100,700,500);

    #elif SOLVER_TEST == IVP_PICARD

      fig.setProperties(100,100,700,500);

    #elif SOLVER_TEST == DAE

      fig.setProperties(100,100,700,500);

    #elif SOLVER_TEST == BVP

      fig.setProperties(100,100,700,350);
      Trajectory truth1(domain, Function("t", "exp(t)/sqrt(1+exp(2))"));
      fig.addTrajectory(&truth1, "truth1", "blue");
      Trajectory truth2(domain, Function("t", "-exp(t)/sqrt(1+exp(2))"));
      fig.addTrajectory(&truth2, "truth2", "red");

    #elif SOLVER_TEST == BVP_CP2010

      fig.setProperties(100,100,700,350);

    #elif SOLVER_TEST == DELAY

      fig.setProperties(100,100,700,350);

    #endif

    for(int i = 0 ; i < v_solutions.size() ; i++)
    {
      cout << i << ": " << v_solutions[i] << endl;
      ostringstream o;
      o << "solution_" << i;
      fig.addTube(&v_solutions[i], o.str());
      //fig.setTubeDerivative(&v_solutions[i], &v_solutions[i]);
    }

    if(!v_solutions.empty())
      fig.show(show_details);
    vibes::endDrawing();

  return EXIT_SUCCESS;
}