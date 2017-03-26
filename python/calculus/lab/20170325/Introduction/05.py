#La banca se depun 100 Euro cu doamnda de 5% pe an.
#In momentul in care se atinge suma de 200 Euro banii vor fi retrasi.
#dupa cati ani este posibil acest lucru?
bani=100
dobanda=1.05
ani=0
while bani<200:
    bani=bani*dobanda
    ani=ani+1
print('Sunt necesari ', ani, 'ani pentru a ajunge la ',bani,' euro')
