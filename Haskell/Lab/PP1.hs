suma::(Int,Int)->Int
suma (x,y)=x+y

signvp::Float->Int

signvp x=if (x<=0)  then 0
                    else 1

signer::Float->Int
signer x| (x<0)= -1
        | (x==0)= 0
        | otherwise= 1                    


xor::Bool->Bool->Bool
xor True True=False 
xor False False=False 
xor _ _=True   

cmmdc::Int->Int->Int
cmmdc d 0=d
cmmdc d i=cmmdc i (d `mod`i)

main::IO()
main= do
        putStrLn "Primul numar:"
        nr1<-getLine;
        putStrLn "Al doilea numar:"
        nr2<-getLine;
        print(cmmdc (read nr1) (read nr2))
        invlist[1,2,3,4]
        putStrLn ""

--inversarea unei liste de numere intregi
invlist::[Integer]->IO()
invlist []=putStrLn "Lista inversata..."
invlist (cap:rl)=do{
        invlist rl;
        putStr (show cap);
}

--calculeaza de cate ori apare un string intr-o lsita de stringuri
contapsc::[[Char]]->String->Int
contapsc [] _=0
contapsc(cap:rl) cc | (cc==cap)=1+contapsc rl cc
                    | otherwise=contapsc rl cc

--stergerea unui element
--si afiseaza ce ramane
delapsc::[[Char]]->String->[[Char]]
delapsc [] _=[]
delapsc (sc:rl) cd |(cd/=sc)=sc:(delapsc rl cd)
                   |otherwise=delapsc rl cd

--afiseaza de cate se repeta fiecare string dint-o lista de stringuri
statcuvl::[[Char]]->[(String,Int)]
statcuvl []=[]
statcuvl (cap:rl)=(cap,contapsc (cap:rl) cap):statcuvl (delapsc rl cap)
