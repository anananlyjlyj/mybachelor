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
# harmonic oscillator
omega = 2*np.pi;
dia = m/2*omega**2*xvec**2
# =============================================================================


#plot potential
#plt.figure(2)
#plt.clf()
#plt.plot(xvec,dia)

#potential energy as matrix
Epot = np.mat(np.diag(dia,0))
#%% combine to Hamiltonian, diagonalize and plot the lowest 30 energy eigenvalues

H =  Ekin + Epot

w, v = LA.eig(H)
sortinds = np.argsort(w)
EigVecs = v[:,sortinds]
EigVals = w[sortinds]

# plot Eigenvalues (spectrum)
#plt.figure(3)
#plt.clf()
#plt.plot(EigVals[0:30],'o')

#%%

Zero = EigVecs[:,0]
EZero = EigVals[0]

One = EigVecs[:,1]
EOne = EigVals[1]

Two = EigVecs[:,2]
ETwo = EigVals[2]

fig = plt.figure(1)
ax1 = fig.add_subplot(2,2,1)
ax2 = fig.add_subplot(2,2,2)
ax3 = fig.add_subplot(2,2,3)
ax4 = fig.add_subplot(2,2,4)

# revival time of the D state (Q revival ist at half this time)
trev = 2*np.pi*hbar/(EOne-EZero)
NSteps = 20
NOsc = 3
dt = trev/NSteps

t = 0
for k in range(0,NSteps*NOsc):
    D = 1/np.sqrt(2)*(np.exp(-1j*EZero/hbar*t)*Zero + np.exp(-1j*EOne/hbar*t)*One)
    Q = 1/np.sqrt(2)*(np.exp(-1j*EZero/hbar*t)*Zero + np.exp(-1j*ETwo/hbar*t)*Two)
    t = t+dt
    
    ax1.cla()
    ax2.cla()
    ax1.plot(xvec,np.power(np.abs(D),2))
    ax2.plot(xvec,np.real(D))
    ax2.plot(xvec,np.imag(D))
    ax1.set_xlim([-3,3])
    ax2.set_xlim([-3,3])
    
    ax3.cla()
    ax4.cla()
    ax3.plot(xvec,np.power(np.abs(Q),2))
    ax4.plot(xvec,np.real(Q))
    ax4.plot(xvec,np.imag(Q))
    ax3.set_xlim([-3,3])
    ax4.set_xlim([-3,3])

    fig.canvas.draw()
    plt.pause(0.0001)

#%% Show eigenfunctions (use left/right arrow to go through)
#pos = 0
#def key_event(e):
#    global pos
#    if e.key == 'right':
#        pos += 1
#    elif e.key == 'left':
#        pos -= 1
#    else:
#        return
#    pos = pos % EigVecs.shape[1]
#
#    ax1.cla()
#    ax1.plot(xvec,np.real(EigVecs[:,pos]))
#    ax1.set(title='Realteil Eigenfunktion %d'%(pos+1),xlabel='x')
#
#    ax2.cla()
#    ax2.plot(xvec,np.power(np.abs(EigVecs[:,pos]),2))
#    ax2.set(title='AbsQuadrat Eigenfunktion %d'%(pos+1),xlabel='x')
#
#    fig.canvas.draw()
#
#fig = plt.figure(1)
#ax1 = fig.add_subplot(1,2,1)
#ax2 = fig.add_subplot(1,2,2)
#fig.canvas.mpl_connect('key_press_event', key_event)
#
#ax1.cla()
#ax1.plot(xvec,np.real(EigVecs[:,pos]))
#ax1.set(title='Realteil Eigenfunktion %d'%(pos+1),xlabel='x')
#
#ax2.cla()
#ax2.plot(xvec,np.power(np.abs(EigVecs[:,pos]),2))
#ax2.set(title='AbsQuadrat Eigenfunktion %d'%(pos+1),xlabel='x')