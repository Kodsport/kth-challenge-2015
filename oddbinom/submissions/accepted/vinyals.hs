completesum m = (iterate (*3) 2) !! m

partialsum n m
  | n == 0 = 0
  | m == 0 = 2
  | remain >=0 = (completesum (m-1)) + 2*(partialsum remain (m-1))
  | otherwise = partialsum n (m-1)
  where remain = n-2^(m-1)

solve' n m
  | 2^m <= n  = (completesum m) + (solve' (n-2^m) (m+1))
  | otherwise = partialsum n m
  
solve n = solve' n 0

moin str = show (solve ((read str :: Int)-1)+1)
main = interact moin
