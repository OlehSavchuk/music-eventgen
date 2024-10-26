#!/bin/bash

################
## GRIDPARAMS ##
################
GRIDMAX=25
GRIDSTEP="0.1002"

NEVENTS=1000

cat > input-trento.dat << END

# specify the projectile option twice
projectile = Pb
projectile = Pb
number-events = $NEVENTS

# don't print event properties to stdout, save to HDF5
quiet = true
output = PbPb.hdf

reduced-thickness = $7
fluctuation = 1
nucleon-width = 0.5
cross-section = 6.4
normalization = $6

# leave commented out for min-bias
b-min = $1
b-max = $2

grid-max = $GRIDMAX
grid-step = $GRIDSTEP
END
cp ./input-trento.dat ./trento

echo Trento started running
./trento/trento -c ./trento/input-trento.dat -o ./trento/to_average

echo trento finished running

GRIDPOINTS=500

./trento-average.py ./trento/to_average/ $NEVENTS $GRIDPOINTS $GRIDSTEP
wait
rm -r ./trento/to_average
cp ./trento/music-input-from-trento.dat ./music-hydro/

cd music-hydro
cat > PCE_inputfile.dat << END


###################################
# parameters to play with
###################################
#initial distribution
Initial_Distribution_input_filename music-input-from-trento.dat
#chemical equilibrium params
Initial_light_quark_fugacity 1  # initial fugacities 
Initial_strange_quark_fugacity 1
Light_quark_equilibration_time 5 # equilibration timescales (fm/c)
Strange_quark_equilibration_time 0

# transport coefficients
Viscosity_Flag_Yes_1_No_0 1     # turn on viscosity in the evolution
Include_Shear_Visc_Yes_1_No_0 1 # include shear viscous effect
Shear_to_S_ratio 0.1            # value of \eta/s
T_dependent_Shear_to_S_ratio 3  # flag to use temperature dep. \eta/s(T)
eta_over_s_T_kink_in_GeV 0.17
eta_over_s_low_T_slope_in_GeV $8
eta_over_s_high_T_slope_in_GeV $5
eta_over_s_at_kink $4

Include_Bulk_Visc_Yes_1_No_0 1  # include bulk viscous effect
T_dependent_Bulk_to_S_ratio 2
bulk_viscosity_normalisation $3
bulk_viscosity_width_in_GeV 0.01
bulk_viscosity_peak_in_GeV 0.17

s_factor 60                   # normalization factor read in
END
cat example_inputfiles/PCE_short.txt >> PCE_inputfile.dat
./MUSIChydro ./PCE_inputfile.dat
