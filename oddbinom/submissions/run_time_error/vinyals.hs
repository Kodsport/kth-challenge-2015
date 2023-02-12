pascalrow x@(_:xs) = [1] ++ zipWith (+) x xs ++ [1]

pascal 0 = [[1]]
pascal n = (pascalrow h:x)
  where x@(h:_) = pascal (n-1)

countodd x = length (filter (\x -> (x `mod` 2 == 1)) x)

solve n = countodd (concat(pascal n))

moin str = show (solve ((read str :: Int)-1))
main = interact moin
