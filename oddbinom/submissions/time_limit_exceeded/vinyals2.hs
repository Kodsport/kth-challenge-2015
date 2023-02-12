gen x = x ++ map (*2) x
s = concat (iterate gen [2])

solve n = sum(take n s)

moin str = show (solve ((read str :: Int)-1)+1)
main = interact moin
