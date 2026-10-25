"""P&O MPPT vs fixed-voltage (PWM-like) operation on a single-diode PV model.
Ideal converter, no losses: results are an upper bound, not a measurement."""
import numpy as np, matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from scipy.optimize import brentq
ISC0, VOC, VMP_T = 5.8, 21.7, 18.3
def model(a,isc): 
    i0=isc/(np.exp(VOC/a)-1); return lambda v: np.maximum(isc-i0*(np.exp(v/a)-1),0)
def vmp(a):
    v=np.linspace(0.1,VOC,4000); p=v*model(a,ISC0)(v); return v[p.argmax()]
A=brentq(lambda a:vmp(a)-VMP_T,0.8,4)
def power(v,g):
    isc=ISC0*g; i0=ISC0/(np.exp(VOC/A)-1)
    return v*max(isc-i0*(np.exp(v/A)-1),0)
t=np.linspace(0.25,11.75,1381)                     # 12 h day, 30 s steps
g=np.sin(np.pi*t/12)**1.2; g[(t>5.0)&(t<5.3)]*=0.45   # passing cloud
V_PWM=13.0; v=V_PWM+2; step=0.15
pp=[];pw=[];vs=[];pprev=0;vprev=v
for gi in g:
    p=power(v,gi); 
    if p>=pprev: d=(np.sign(v-vprev) or 1)
    else: d=-(np.sign(v-vprev) or 1)
    vprev=v; pprev=p; v=min(max(v+d*step,5),VOC-0.5)
    pp.append(p); pw.append(power(V_PWM,gi)); vs.append(vprev)
pp=np.array(pp);pw=np.array(pw)
gain=pp.sum()/pw.sum()-1
mpp=np.array([max(power(x,gi) for x in np.linspace(5,21,200)) for gi in g])
print(f"energy gain {gain*100:.1f}%  tracking eff {pp.sum()/mpp.sum()*100:.1f}%  pwm eff {pw.sum()/mpp.sum()*100:.1f}%")
fig,ax=plt.subplots(figsize=(6.2,3.4),dpi=250)
ax.plot(t,mpp,color="#94A3B8",lw=1,ls="--",label="Available (true MPP)")
ax.plot(t,pp,color="#047857",lw=1.6,label="P&O MPPT")
ax.plot(t,pw,color="#B91C1C",lw=1.6,label="Fixed 13 V (PWM-like)")
ax.set_xlabel("Hours after sunrise");ax.set_ylabel("Panel power (W)")
ax.spines[["top","right"]].set_visible(False);ax.legend(frameon=False,fontsize=7);ax.tick_params(labelsize=7)
ax.xaxis.label.set_size(8);ax.yaxis.label.set_size(8);ax.grid(alpha=.25)
fig.tight_layout();fig.savefig("sim.png")
