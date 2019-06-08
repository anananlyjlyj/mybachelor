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
#harmonic oscillator
#omega = 2*np.pi;
#dia = m/2*omega**2*xvec**2
# =============================================================================

# =============================================================================
#potential well
#width = 15
#dia = 100*np.ones(xvec.shape)
#dia[np.abs(xvec)<width/2]=0
# =============================================================================

# =============================================================================
#square double well
#width = 15
#widthbarr = 2
#barrheight = 3
#dia = 100*np.ones(xvec.shape)
#dia[np.abs(xvec)<width/2] = 0
#dia[np.abs(xvec)<widthbarr/2] = barrheight
# =============================================================================

# =============================================================================
##gravitational potential with mirror
offset = 0.2
g = 5
StartInd = np.where(xvec-xvec[0]>offset)[0][0]
dia = m*g*(xvec-xvec[StartInd])
dia[0:StartInd]=1000
# =============================================================================

# =============================================================================
## abs(x)
#dia = 50*np.abs(xvec)
# =============================================================================

# =============================================================================
## sqrt(abs(x))
#dia = 50*np.sqrt(np.abs(xvec))
# =============================================================================

# =============================================================================
## some weird function
#dia = 100*np.cos(np.pi/5*xvec)**2*np.log(np.abs(xvec))
#dia[np.isinf(dia)]=-400
# =============================================================================

#plot potential
plt.figure(2)
plt.clf()
plt.plot(xvec,dia)

#potential energy as matrix
Epot = np.mat(np.diag(dia,0))
#%% combine to Hamiltonian, diagonalize and plot the lowest 30 energy eigenvalues

H =  Ekin + Epot

w, v = LA.eig(H)
sortinds = np.argsort(w)
EigVecs = v[:,sortinds]
EigVals = w[sortinds]

# plot Eigenvalues (spectrum)
plt.figure(3)
plt.clf()
plt.plot(EigVals[0:30],'o')

#%% Show eigenfunctions (use left/right arrow to go through)
pos = 0
def key_event(e):
    global pos
    if e.key == 'right':
        pos += 1
    elif e.key == 'left':
        pos -= 1
    else:
        return
    pos = pos % EigVecs.shape[1]

    ax1.cla()
    ax1.plot(xvec,np.real(EigVecs[:,pos]))
    ax1.set(title='Realteil Eigenfunktion %d'%(pos+1),xlabel='x')

    ax2.cla()
    ax2.plot(xvec,np.power(np.abs(EigVecs[:,pos]),2))
    ax2.set(title='AbsQuadrat Eigenfunktion %d'%(pos+1),xlabel='x')

    fig.canvas.draw()

fig = plt.figure(1)
ax1 = fig.add_subplot(1,2,1)
ax2 = fig.add_subplot(1,2,2)
fig.canvas.mpl_connect('key_press_event', key_event)

ax1.cla()
ax1.plot(xvec,np.real(EigVecs[:,pos]))
ax1.set(title='Realteil Eigenfunktion %d'%(pos+1),xlabel='x')

ax2.cla()
ax2.plot(xvec,np.power(np.abs(EigVecs[:,pos]),2))
ax2.set(title='AbsQuadrat Eigenfunktion %d'%(pos+1),xlabel='x')