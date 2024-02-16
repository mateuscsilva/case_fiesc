push!(LOAD_PATH, "modules/")
using Pkg
using Gurobi

import Data
import Formulations

inst = Data.read()

Formulations.formulation0(inst)