#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import scipy.constants as const
import scipy.fftpack as ft
from numpy import linalg as LA
import time

#%% Set parameters and grid size

hbar = 1
m = 1

Ngrid = 2000
xmin = -30
xmax = 30

x = np.linspace(xmin,xmax,Ngrid)
dx = np.diff(x).mean()

k = ft.fftfreq(x.size,d = dx)
k = 2*np.pi*ft.fftshift(k)
dk = np.diff(k).mean()

# define potential (in real space) and kinetic energy (in k-space)

## potential well with high walls
#Vpot = np.zeros(x.size)
#Vpot[x>0] = 0
#Vpot[x<-20] = 1e6
#Vpot[x>20] = 1e6

# harmonic oscillator
#omega = 2*np.pi*0.5
#Vpot = (m/2)*omega**2*x**2

# free evolution: No potential
Vpot = np.zeros(x.size)

Ekin = hbar**2*k**2/(2*m)

# initial state: Gaussian wave packet with mean k and mean x
#sig = np.sqrt(hbar/(m*omega))
sig = 1
x0 = 0
k0 = 0
#k0 = 100*dk
Psi = np.exp(-(x-x0)**2/(2*sig**2))
Psi = Psi/np.sqrt(np.sum(np.abs(Psi)**2))
#Psik = ft.fftshift(ft.fft(Psi))
Psik = ft.fftshift(ft.fft(ft.fftshift(Psi)))
Psik = np.roll(Psik,np.int(np.round(k0/dk)))
Psi = ft.fftshift(ft.ifft(ft.fftshift(Psik)))

dt = 0.5e-3
tfin = 4;

M = round(tfin/dt)

ts = np.nan*np.ones(M)
calcval = np.nan*np.ones(M)
calcval2 = np.nan*np.ones(M)

fig = plt.figure(1)
ax1 = fig.add_subplot(2,2,1)
ax2 = fig.add_subplot(2,2,3)
ax3 = fig.add_subplot(2,2,2)
ax4 = fig.add_subplot(2,2,4)

t = 0
count=0
valcount=0
for m in range(0,M,1):
    t = t+dt
    count = count+1
    #print(t)
    Psi = np.exp(-1j*Vpot/hbar*dt)*Psi                      # advance in real-space
    Psik = ft.fftshift(ft.fft(ft.fftshift(Psi)))            # Fourier transform
    Psik = np.exp(-1j*Ekin/hbar*dt)*Psik                    # advance in Fourier space
    Psi = ft.fftshift(ft.ifft(ft.fftshift(Psik)))           # return to real space
    
    if count>100:
        count=0
        
        #calculate mean values to plot
        ts[valcount]=t
        meank = np.sum(np.conj(Psik)*k*Psik)
        meank = np.real(meank)
        meank2 = np.sum(np.conj(Psik)*k**2*Psik)
        meank2 = np.real(meank2)
        meanx = np.sum(np.conj(Psi)*x*Psi)
        meanx = np.real(meanx)
        meanx2 = np.sum(np.conj(Psi)*x**2*Psi)
        meanx2 = np.real(meanx2)
        
        calcval[valcount] = np.sqrt(meanx2-meanx**2)
        calcval2[valcount] = np.sqrt(meank2-meank**2)
        valcount+=1
        
        ax1.cla()
        ax2.cla()
        ax1.plot(x,np.abs(Psi))
        plotval = np.unwrap(np.angle(Psi))
        plotval[np.abs(Psi)<1e-10] = np.nan
        plotval = plotval-np.min(plotval[~np.isnan(plotval)])
        ax2.plot(x,plotval)
        ax2.set_ylim([-1,100])
        ax2.set_xlim([-30,30])
        ax1.set_title('Ortsraum')
        
        ax3.cla()
        ax3.plot(k,np.abs(Psik))
        ax4.cla()
        plotval =  np.unwrap(np.angle(Psik))
        plotval[np.abs(Psik)<1e-10] = np.nan
        plotval = plotval-np.max(plotval[~np.isnan(plotval)])
        ax4.plot(k,plotval)
        ax4.set_ylim([-100,1])
        ax3.set_xlim([-10,10])
        ax4.set_xlim([-10,10])
        ax3.set_title('Impulsraum')
        
        
        #ax4.set_ylim([-150,10])
        #ax2.plot(ts,calcval2)
        #ax2.plot(k,np.power(np.abs(Psik),2))

        fig.canvas.draw()
        plt.pause(0.0001)