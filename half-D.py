import openmc
import openmc.mgxs
import openmc.deplete
import os
import sys

num_procs = 1
if len(sys.argv) > 1:
    num_procs = sys.argv[1]

os.environ["OMP_NUM_THREADS"] = num_procs

model = openmc.Model()
#openmc.deplete.pool.NUM_PROCESSES = num_procs

materials = openmc.Materials.from_xml('msbr-data/msbr-materials.xml')
fuel = materials[0]
fuel.add_nuclide('U233',0.025,'wo')
model.materials = openmc.Materials([fuel])

bottom, top = [openmc.ZPlane(z0 = v, boundary_type = 'reflective') for v in [-10,10]] 
cyl = openmc.ZCylinder(r=9,boundary_type = 'reflective')
cell = openmc.Cell(name = 'core', fill = fuel, region= -cyl & +bottom & -top)
uni = openmc.Universe(cells = [cell])
model.geometry.root_universe = uni

model.settings.particles = 10000
model.settings.batches = 100
model.settings.inactive = 50
model.settings.source = openmc.IndependentSource(space=openmc.stats.Box([-9, -9, -10], 
                                                                        [9, 9, 10]), constraints = {'fissionable':True})

operator = openmc.deplete.CoupledOperator(model, 'msbr-data/chain_endfb71_pwr.xml')
integrator = openmc.deplete.LEQIIntegrator(operator=operator, timesteps=[(4*n) / (n+3) for n in range(1,101)], power=1e9)

integrator.integrate(output=False)
