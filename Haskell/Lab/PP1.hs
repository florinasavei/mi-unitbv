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


invlist::[Integer]->IO()
invlist []=putStrLn "Lista inversata..."
invlist (cap:r1)=do{
        invlist r1;
        putStr (show cap);
}