print("Script started")

test = 1000

print("test value: "..test)

function simple_test()
	print("Fuction called")
	
	print("testing vectors")
	local vec1 = math.vector3d.create{ x=1,y=3,z=0}
    local vec2 = math.vector3d.create{ x=0,y=1,z=0}
    local vec3 = vec1*3 + vec2 - vec2*vec1;
    print ( vec3.x..", "..vec3.y..", "..vec3.z )
    print ( "Dot product of vec3,vec3 "..math.dot(vec3,vec3) )
    local vec4 = math.vector3d.i
    
    local quat = math.createRotationQuat(math.pi,vec4)
    vec3  = quat:rotate(math.vector3d.j)
    print ( vec3.x..", "..vec3.y..", "..vec3.z )
    local mtx4 = math.createXRotationMatrix4x4(math.pi*0.5)
   
    vec3  = mtx4*vec2
    print ( vec3.x..", "..vec3.y..", "..vec3.z )
    local quat1 = math.quaternionFromMatrix4x4(mtx4)
    local mtx3	= math.matrix3x3FromQuaternion(quat1)
	vec3  = mtx4*vec2
    print ( vec3.x..", "..vec3.y..", "..vec3.z )

    vec1:delete()
    vec2:delete()
    vec3:delete()
    quat:delete()
    quat1:delete()
    mtx4:delete()
    mtx3:delete()
    --vec4:delete()
end

print("Calling from script")

simple_test()

function par1(p)
	print(p)
	return p;
end

function par2(p1,p2)
	print(p1.." "..p2);
	return p1,p2;
end