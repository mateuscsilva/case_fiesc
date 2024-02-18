module Data

struct InstanceData
  NM::Int #number of machines
  NOP::Int #number of OPs
  opList::Matrix{Int}
  machineList::Matrix{Int}
	cutMachineSetup::Int
	opListCutTime::Matrix{Int}
	cutMachineTableChange::Int
	opSize::Matrix{Int}
end

export InstanceData


function readV0()
 	NM = 2
	NOP = 4
	cutMachineSetup = 4
	cutMachineTableChange = 5

	opList = zeros(Int, NOP, 2)
	machineList = zeros(Int, NM, 2)
	opListCutTime = zeros(Int, NOP, 2)
	opSize = zeros(Int, NOP, 2)

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


	instNEW = InstanceData(NM, NOP,opList,machineList, cutMachineSetup, opListCutTime, cutMachineTableChange, opSize)

	return instNEW

end

function readV1()
 NM = 1
 NOP = 4
 cutMachineSetup = 4
 cutMachineTableChange = 5

 opList = zeros(Int, NOP, 2)
 machineList = zeros(Int, NM, 2)
 opListCutTime = zeros(Int, NOP, 2)
 opSize = zeros(Int, NOP, 2)

 opList[1] = 18
 opList[2] = 14
 opList[3] = 12
 opList[4] = 6

 machineList[1] = 2

 opListCutTime[1] = 4
 opListCutTime[2] = 4
 opListCutTime[3] = 6
 opListCutTime[4] = 6	


 instNEW = InstanceData(NM, NOP,opList,machineList, cutMachineSetup, opListCutTime, cutMachineTableChange, opSize)

 return instNEW

end

function readV2()
	NM = 2
	NOP = 9
	cutMachineSetup = 4
	cutMachineTableChange = 5
 
	opList = zeros(Int, NOP, 2)
	machineList = zeros(Int, NM, 2)
	opListCutTime = zeros(Int, NOP, 2)
	opSize = zeros(Int, NOP, 2)
 
	opList[1] = 18
	opList[2] = 14
	opList[3] = 12
	opList[4] = 6
	opList[5] = 36
	opList[6] = 9
	opList[7] = 9
	opList[8] = 12
	opList[9] = 12
 
	machineList[1] = 2
	machineList[2] = 3
 
	opListCutTime[1] = 4
	opListCutTime[2] = 4
	opListCutTime[3] = 6
	opListCutTime[4] = 6	
	opListCutTime[5] = 12
	opListCutTime[6] = 6
	opListCutTime[7] = 2
	opListCutTime[8] = 2
	opListCutTime[9] = 4	
 
	opSize[1] = 3
	opSize[2] = 3
	opSize[3] = 4
	opSize[4] = 4	
	opSize[5] = 8
	opSize[6] = 6
	opSize[7] = 2
	opSize[8] = 2
	opSize[9] = 4
 
	instNEW = InstanceData(NM, NOP,opList,machineList, cutMachineSetup, opListCutTime, cutMachineTableChange, opSize)
 
	return instNEW
 
 end

end
