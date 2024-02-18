push!(LOAD_PATH, "modules/")
using Pkg
using Gurobi

import Data
import Formulations


#inst = Data.readV0()
#Formulations.formulation0(inst)

inst = Data.readV1()
Formulations.formulation1(inst)

#inst = Data.readV2()
#Formulations.formulation2(inst)