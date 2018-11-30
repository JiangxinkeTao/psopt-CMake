//////////////////////////////////////////////////////////////////////////
////////////////           steps.cxx                 /////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////           PSOPT example             /////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////// Title: 	Steps problem                     ////////////////
//////// Last modified: 12 July 2009                      ////////////////
//////// Reference:      Gong, Farhoo, and Ross (2008)    ////////////////
////////                                                  ////////////////
//////////////////////////////////////////////////////////////////////////
////////     Copyright (c) Victor M. Becerra, 2009        ////////////////
//////////////////////////////////////////////////////////////////////////
//////// This is part of the PSOPT software library, which ///////////////
//////// is distributed under the terms of the GNU Lesser ////////////////
//////// General Public License (LGPL)                    ////////////////
//////////////////////////////////////////////////////////////////////////

#include "psopt.h"


//////////////////////////////////////////////////////////////////////////
///////////////////  Define the end point (Mayer) cost function //////////
//////////////////////////////////////////////////////////////////////////


adouble endpoint_cost(adouble* initial_states, adouble* final_states,
                      adouble* parameters,adouble& t0, adouble& tf,
                      adouble* xad, int iphase, Workspace* workspace)
{
   	return 0.0;
}

//////////////////////////////////////////////////////////////////////////
///////////////////  Define the integrand (Lagrange) cost function  //////
//////////////////////////////////////////////////////////////////////////

adouble integrand_cost(adouble* states, adouble* controls, adouble* parameters,
                     adouble& time, adouble* xad, int iphase, Workspace* workspace)
{
   adouble x = states[ CINDEX(1) ];

   return (x);
}


//////////////////////////////////////////////////////////////////////////
///////////////////  Define the DAE's ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void dae(adouble* derivatives, adouble* path, adouble* states,
         adouble* controls, adouble* parameters, adouble& time,
         adouble* xad, int iphase, Workspace* workspace)
{

    adouble u = controls[CINDEX(1)];

    derivatives[ CINDEX(1) ]  = u;

}

////////////////////////////////////////////////////////////////////////////
///////////////////  Define the events function ////////////////////////////
////////////////////////////////////////////////////////////////////////////

void events(adouble* e, adouble* initial_states, adouble* final_states,
            adouble* parameters,adouble& t0, adouble& tf, adouble* xad,
            int iphase, Workspace* workspace)

{

    adouble x1_i 	= initial_states[ CINDEX(1) ];

    adouble x1_f 	= final_states[ CINDEX(1) ];


   if ( iphase==1 ) {
		    e[ CINDEX(1) ] =  x1_i;
   }
   else if ( iphase==3 ) {
		    e[ CINDEX(1) ] = x1_f;
   }

}



///////////////////////////////////////////////////////////////////////////
///////////////////  Define the phase linkages function ///////////////////
///////////////////////////////////////////////////////////////////////////

void linkages( adouble* linkages, adouble* xad, Workspace* workspace)
{

}



////////////////////////////////////////////////////////////////////////////
///////////////////  Define the main routine ///////////////////////////////
////////////////////////////////////////////////////////////////////////////

int main(void)
{

////////////////////////////////////////////////////////////////////////////
///////////////////  Declare key structures ////////////////////////////////
////////////////////////////////////////////////////////////////////////////

    Alg  algorithm;
    Sol  solution;
    Prob problem;
    MSdata msdata;

////////////////////////////////////////////////////////////////////////////
///////////////////  Register problem name  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////

    problem.name        		= "Steps problem";
    problem.outfilename                 = "steps.txt";

////////////////////////////////////////////////////////////////////////////
////////////  Define problem level constants & do level 1 setup ////////////
////////////////////////////////////////////////////////////////////////////

    msdata.nsegments       = 3;
    msdata.nstates         = 1;
    msdata.ncontrols       = 1;
    msdata.nparameters     = 0;
    msdata.npath           = 0;
    msdata.ninitial_events = 1;
    msdata.nfinal_events   = 1;
    msdata.nodes           = 20; // nodes per segment

    multi_segment_setup(problem, algorithm, msdata );

////////////////////////////////////////////////////////////////////////////
///////////////////  Enter problem bounds information //////////////////////
////////////////////////////////////////////////////////////////////////////


    problem.phases(1).bounds.lower.controls(1) = -2.0;
    problem.phases(1).bounds.upper.controls(1) =  2.0;
    problem.phases(1).bounds.lower.states(1) = 0.0;
    problem.phases(1).bounds.upper.states(1) = 5.0;
    problem.phases(1).bounds.lower.events(1) = 3.0;
    problem.phases(3).bounds.lower.events(1) = 1.0;


    problem.phases(1).bounds.upper.events=problem.phases(1).bounds.lower.events;
    problem.phases(3).bounds.upper.events=problem.phases(3).bounds.lower.events;



    problem.phases(1).bounds.lower.StartTime    = 0.0;
    problem.phases(1).bounds.upper.StartTime    = 0.0;

    problem.phases(3).bounds.lower.EndTime      = 3.0;
    problem.phases(3).bounds.upper.EndTime      = 3.0;

//    problem.bounds.lower.times = "[0.0, 1.0, 2.0, 3.0]";
//    problem.bounds.upper.times = "[0.0, 1.0, 2.0, 3.0]";

    problem.bounds.lower.times = "[0.0, 1.0, 2.0, 3.0]";
    problem.bounds.upper.times = "[0.0, 1.0, 2.0, 3.0]";

    auto_phase_bounds(problem);



////////////////////////////////////////////////////////////////////////////
///////////////////  Register problem functions  ///////////////////////////
////////////////////////////////////////////////////////////////////////////


    problem.integrand_cost 	= &integrand_cost;
    problem.endpoint_cost 	= &endpoint_cost;
    problem.dae             	= &dae;
    problem.events 		= &events;
    problem.linkages		= &linkages;

////////////////////////////////////////////////////////////////////////////
///////////////////  Define & register initial guess ///////////////////////
////////////////////////////////////////////////////////////////////////////

    int nnodes    			= problem.phases(1).nodes(1);
    int ncontrols                       = problem.phases(1).ncontrols;
    int nstates                         = problem.phases(1).nstates;

    DMatrix state_guess    =  zeros(nstates,nnodes);
    DMatrix control_guess  =  zeros(ncontrols,nnodes);
    DMatrix time_guess     =  linspace(0.0,3.0,nnodes);
    DMatrix param_guess;



    state_guess(1,colon()) = linspace(1.0, 1.0, nnodes);

    control_guess(1,colon()) = zeros(1,nnodes);


    auto_phase_guess(problem, control_guess, state_guess, param_guess, time_guess);

////////////////////////////////////////////////////////////////////////////
///////////////////  Enter algorithm options  //////////////////////////////
////////////////////////////////////////////////////////////////////////////


    algorithm.nlp_iter_max                = 1000;
    algorithm.nlp_tolerance               = 1.e-6;
    algorithm.nlp_method                  = "IPOPT";
    algorithm.scaling                     = "automatic";
    algorithm.derivatives                 = "automatic";
    algorithm.hessian                     = "exact";
    algorithm.mesh_refinement             = "automatic";
    algorithm.ode_tolerance               = 1.e-5;


////////////////////////////////////////////////////////////////////////////
///////////////////  Now call PSOPT to solve the problem   //////////////////
////////////////////////////////////////////////////////////////////////////

    psopt(solution, problem, algorithm);

////////////////////////////////////////////////////////////////////////////
///////////  Extract relevant variables from solution structure   //////////
////////////////////////////////////////////////////////////////////////////


    DMatrix x, u, t, xi, ui, ti;

    x      = solution.get_states_in_phase(1);
    u      = solution.get_controls_in_phase(1);
    t      = solution.get_time_in_phase(1);

    for(int i=2;i<=problem.nphases;i++) {
      	     xi      = solution.get_states_in_phase(i);
    	     ui      = solution.get_controls_in_phase(i);
    	     ti      = solution.get_time_in_phase(i);

	x = x || xi;

        u = u || ui;

        t = t || ti;

    }


////////////////////////////////////////////////////////////////////////////
///////////  Save solution data to files if desired ////////////////////////
////////////////////////////////////////////////////////////////////////////

    x.Save("x.dat");
    u.Save("u.dat");
    t.Save("t.dat");

////////////////////////////////////////////////////////////////////////////
///////////  Plot some results if desired (requires gnuplot) ///////////////
////////////////////////////////////////////////////////////////////////////

    plot(t,x(1,colon()),problem.name+": state","time (s)", "x", "x");

    plot(t,u(1,colon()),problem.name+": control","time (s)", "u", "u");

    plot(t,x(1,colon()),problem.name+": state","time (s)", "x", "x",
	                                "pdf", "steps_state.pdf");


    plot(t,u(1,colon()),problem.name+": control","time (s)", "u", "u",
	                                "pdf", "steps_control.pdf");


}

////////////////////////////////////////////////////////////////////////////
///////////////////////      END OF FILE     ///////////////////////////////
////////////////////////////////////////////////////////////////////////////
