module Data

struct InstanceData
  NM::Int #number of machines
  NOP::Int #number of OPs
  opList::Matrix{Int}
  machineList::Matrix{Int}
end

export InstanceData


function read()
 	NM = 2
	NOP = 4
	
	opList = zeros(Int, NOP, 2)
	machineList = zeros(Int, NM, 2)

	opList[1] = 12
	opList[2] = 10
	opList[3] = 8
	opList[4] = 4

	machineList[1] = 2
	machineList[2] = 3


	instNEW = InstanceData(NM, NOP,opList,machineList)

	return instNEW

end

end
