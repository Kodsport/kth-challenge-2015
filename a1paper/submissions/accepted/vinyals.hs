solve' n [] a = 0/0
solve' n (h:t) a
  | h >= n = 0.0
  | otherwise = (fromIntegral (n-h))*a + solve' ((n-h)*2) t (a/sqrt(2))

solve x = solve' 1 (0:x) (2**(-3/4))

moin str = if isNaN(tape) then "impossible" else show(tape)
  where sizes = [read token :: Int | token <- words ((lines str) !! 1)]
        tape = solve sizes

main = interact moin
