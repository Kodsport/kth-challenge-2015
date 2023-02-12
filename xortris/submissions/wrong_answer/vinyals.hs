import Data.List (transpose)

countx str = length (filter (=='X') str)

solvemn 1 n strl =
  let nx = countx (concat strl)
  in if (n<4) then (nx == 0) else ((nx `mod` 2) == 0)
solvemn m 1 strl = solvemn 1 m strl
solvemn 2 2 strl = countx (concat strl) `mod` 4 == 0
solvemn m n strl = countx (concat strl) `mod` 2 == 0

solve strl =
  let [m,n] = [read token :: Int | token <- words (head strl)]
  in solvemn m n (tail strl)

moin str = if solve (lines str) then "possible\n" else "impossible\n"
main = interact moin
