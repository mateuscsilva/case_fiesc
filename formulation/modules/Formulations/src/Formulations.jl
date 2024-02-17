module Formulations

using JuMP
using Gurobi
using Data
using DataStructures

using Printf

function defineModel()

	model = Model(Gurobi.Optimizer)
	
	#Setting General Parameters
	set_optimizer_attribute(model, "TimeLimit", 3600)
	set_optimizer_attribute(model, "MIPGap", 0.00001)
	
	return model

end



function formulation0(inst::InstanceData)
	println("Running Formulations.stdFormulation")
	model = defineModel()

	BigM = 1000
	### Defining variables ###
	@variable(model, x[i=1:inst.NOP,m=1:inst.NM], Bin)
	@variable(model, y[i=1:inst.NOP,j=1:inst.NOP], Bin)
	@variable(model, 0 <= b[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= f[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= fmax <= BigM, Int)

	### Objective function ###
	@objective(model, Min, fmax)

	@constraint(model, maxTime[i=1:inst.NOP], fmax >= f[i])

	@constraint(model, order[i=1:inst.NOP], sum(y[i,j] for j in 1:inst.NOP) == 1)

	@constraint(model, allocation[j=1:inst.NOP], sum(y[i,j] for i in 1:inst.NOP) == 1)

	@constraint(model, setToMachine[i=1:inst.NOP], sum(x[i,m] for m in 1:inst.NM) == 1)

	@constraint(model, beginAfterFinishTime[i=2:inst.NOP, l=1:inst.NOP, m=1:inst.NM; l<i], b[i] >= f[l] - BigM*(2 - x[i,m] - x[l,m]) )

	@constraint(model, finishTime[i=1:inst.NOP], f[i] == b[i] + sum(y[i,j]*inst.opList[j] for j in 1:inst.NOP) + sum(x[i,m]*inst.machineList[m] for m in 1:inst.NM))

	t1 = time_ns()
	status = optimize!(model)
	t2 = time_ns()
	elapsedtime = (t2-t1)/1.0e9

	nsolutions = result_count(model)
	
	println("Status = ",status)
	if nsolutions > 0

		bestsol = objective_value(model)
		bestbound = objective_bound(model)
		solvertime = solve_time(model)
		solvernodes = node_count(model)
		
		println("Resultscount = ",nsolutions)
		
		println("bestsol = ", bestsol)
		println("Elapsed = ", elapsedtime)
		println("Solver time = ",solvertime)


		open("modelLP.txt", "w") do f
    		print(f, model)
		end

		println("x")
		for i in 1:inst.NOP, m in 1:inst.NM
			if value(x[i,m]) >= 0.000001
				println("$(i),$(m) = 1")
			end
		end

		println("y")
		for i in 1:inst.NOP, j in 1:inst.NOP
			if value(y[i,j]) >= 0.000001
				println("$(i),$(j) = 1")
			end
		end

		println("b")
		for i in 1:inst.NOP
			println("$(value(b[i]))")
		end

		println("f")
		for i in 1:inst.NOP
			println("$(value(f[i]))")
		end
			
	else
		bestsol = "NA"
		bestbound = objective_bound(model)
		solvertime = solve_time(model)
		solvernodes = node_count(model)
	end

end


function formulation1(inst::InstanceData)
	println("Running Formulations.stdFormulation")
	model = defineModel()

	BigM = 1000
	### Defining variables ###
	@variable(model, y[i=1:inst.NOP,j=1:inst.NOP], Bin)
	@variable(model, 0 <= b[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= f[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= bc[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= fc[i=1:inst.NOP] <= BigM, Int)
	@variable(model, 0 <= fmax <= BigM, Int)

	### Objective function ###
	@objective(model, Min, fmax)

	@constraint(model, maxTime[i=1:inst.NOP], fmax >= fc[i])

	@constraint(model, order[i=1:inst.NOP], sum(y[i,j] for j in 1:inst.NOP) == 1)

	@constraint(model, allocation[j=1:inst.NOP], sum(y[i,j] for i in 1:inst.NOP) == 1)

	@constraint(model, beginAfterFinishTime[i=2:inst.NOP, l=1:inst.NOP; l<i], b[i] >= f[l])

	@constraint(model, finishTime[i=1:inst.NOP], f[i] == b[i] + sum(y[i,j]*inst.opList[j] for j in 1:inst.NOP) + inst.machineList[1])

	@constraint(model, beginCutAfterFinishLining[i=1:inst.NOP], bc[i] >= f[i])

	@constraint(model, beginAfterFinishCutTime[i=2:inst.NOP, l=1:inst.NOP; l<i], bc[i] >= fc[l])

	@constraint(model, finishCutTime[i=1:inst.NOP], fc[i] == bc[i] + sum(y[i,j]*inst.opListCutTime[j] for j in 1:inst.NOP) + inst.cutMachineSetup)

	t1 = time_ns()
	status = optimize!(model)
	t2 = time_ns()
	elapsedtime = (t2-t1)/1.0e9

	nsolutions = result_count(model)
	
	println("Status = ",status)
	if nsolutions > 0

		bestsol = objective_value(model)
		bestbound = objective_bound(model)
		solvertime = solve_time(model)
		solvernodes = node_count(model)
		
		println("Resultscount = ",nsolutions)
		
		println("bestsol = ", bestsol)
		println("Elapsed = ", elapsedtime)
		println("Solver time = ",solvertime)


		open("modelLP.txt", "w") do f
    		print(f, model)
		end

		println("y")
		for i in 1:inst.NOP, j in 1:inst.NOP
			if value(y[i,j]) >= 0.000001
				println("$(i),$(j) = 1")
			end
		end

		println("b")
		for i in 1:inst.NOP
			println("$(value(b[i]))")
		end

		println("f")
		for i in 1:inst.NOP
			println("$(value(f[i]))")
		end
			
		println("bc")
		for i in 1:inst.NOP
			println("$(value(bc[i]))")
		end

		println("fc")
		for i in 1:inst.NOP
			println("$(value(fc[i]))")
		end

	else
		bestsol = "NA"
		bestbound = objective_bound(model)
		solvertime = solve_time(model)
		solvernodes = node_count(model)
	end

end


end
