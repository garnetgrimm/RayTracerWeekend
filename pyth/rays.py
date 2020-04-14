from vectors import Point, Vector


rayE = Vector(1,2,3)
rayO = Vector(2,4,6)

plane = Vector(0,4,0)
E = 4

eq = Vector(0,0,0)

rightT=E-plane.dot(rayE)
leftT=plane.dot(rayO)

print(rightT/leftT)

