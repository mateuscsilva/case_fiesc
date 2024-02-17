module Data

struct InstanceData
  NM::Int #number of machines
  NOP::Int #number of OPs
  opList::Matrix{Int}
  machineList::Matrix{Int}
	cutMachineSetup::Int
	opListCutTime::Matrix{Int}
end

export InstanceData


function read()
 	NM = 2
	NOP = 4
	cutMachineSetup = 5

	opList = zeros(Int, NOP, 2)
	machineList = zeros(Int, NM, 2)
	opListCutTime = zeros(Int, NOP, 2)

	opList[1] = 12
	opList[2] = 10
	opList[3] = 8
	opList[4] = 4

	machineList[1] = 2
	machineList[2] = 3

	opListCutTime[1] = 4
	opListCutTime[2] = 4
	opListCutTime[3] = 6
	opListCutTime[4] = 6	


	instNEW = InstanceData(NM, NOP,opList,machineList, cutMachineSetup, opListCutTime)

	return instNEW

end

end
