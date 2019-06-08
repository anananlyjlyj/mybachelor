#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import scipy.constants as const
import scipy.fftpack as ft
from numpy import linalg as LA
import time

#%% define grid and build kinetic energy and momentum operator
hbar = 1
m = 1

Ngrid = 1001
xmin = -10
xmax = 10

xvec = np.linspace(xmin,xmax,Ngrid)
dx = np.diff(xvec).mean()

x = np.mat(np.diag(xvec,0))

#first derivative as operator on the grid (->momentum operator)
dia = 0*np.ones(Ngrid)
offdiap1 = np.ones(Ngrid-1)
offdiam1 = -1*np.ones(Ngrid-1)
d1grid = np.mat(np.diag(dia,0) + np.diag(offdiam1,-1) + np.diag(offdiap1,1))/2/dx
#avoid strange things at the edge of the grid
d1grid[0,:] = 0
d1grid[Ngrid-1,:] = 0

p = hbar/1j*d1grid

#second derivative as operator on the grid (->kinetic energy)
dia = -2*np.ones(Ngrid)
offdia = np.ones(Ngrid-1)
d2grid = np.mat(np.diag(dia,0) + np.diag(offdia,-1) + np.diag(offdia,1))/dx**2
#avoid strange things at the edge of the grid
d2grid[0,:]=0
d2grid[Ngrid-1,:]=0

Ekin = -hbar**2/(2*m)*d2grid

#%%define a potential (diagonal matrix)

# =============================================================================
##gravitational potential with mirror
offset = 0.2
g = 5
StartInd = np.where(xvec-xvec[0]>offset)[0][0]
dia = m*g*(xvec-xvec[StartInd])
dia[0:StartInd]=1000
# =============================================================================

#plot potential
#plt.figure(2)
#plt.clf()
#plt.plot(xvec,dia)

#potential energy as matrix
Epot = np.mat(np.diag(dia,0))
#%% combine to Hamiltonian, diagonalize

H =  Ekin + Epot

w, v = LA.eig(H)
sortinds = np.argsort(w)
EigVecs = v[:,sortinds]
EigVals = w[sortinds]
#transform to matrix
EigVals = np.mat(EigVals).T

#%%
# Gaussian wavepacket
#sig = np.sqrt(hbar/(m*omega))
sig = 0.5
x0 = -4
Psi0 = np.exp(-(xvec-x0)**2/(2*sig**2))
Psi0 = Psi0/np.sqrt(np.sum(np.abs(Psi0)**2))
Psi0 = np.mat(Psi0).T

# EigVecs contains the Eigenvectors as columns, 
# conjugate transpose times Psi0 calculates the scalar product
# of every energy-eigenvector with Psi0 (yields the representation in the energy-eigenbasis)
Psi0Eig = EigVecs.H * Psi0

#%%
fig = plt.figure(1)
ax1 = fig.add_subplot(1,1,1)
ax2 = fig.add_subplot(1,2,2)

tmax = 30
NSteps = 300
dt = tmax/NSteps
calcval = np.nan*np.ones(NSteps)
ts = np.nan*np.ones(NSteps)

t = 0
for k in range(0,NSteps):
    
    # Time evolution is just a phase evolution in the energy eigenbasis
    PsitEig = np.multiply( np.exp(-1j*EigVals/hbar*t),Psi0Eig )
    
    # Transform back to the grid representation (calculate the time-evolved 
    # superposition of energy-eigenstates)
    Psit = EigVecs*PsitEig
    
    # calculate the mean position
    meanx = np.real(Psit.H*x*Psit)
    calcval[k] = np.asscalar(meanx)
    
    t = t+dt
    ts[k]=t
    
    ax1.cla()
    ax1.plot(xvec,np.power(np.abs(Psit),2))
    ax2.cla()
    ax2.plot(ts,calcval)
    #ax1.set_xlim([-3,3])

    fig.canvas.draw()
    plt.pause(0.0001)