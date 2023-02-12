import Data.List (transpose)

flip1 '.' = 'X'
flip1 'X' = '.'
flipfirst3 board = map (\x -> (if snd x < 3 then flip1 else id) (fst x)) (zip board [0..])

solve1dim board | length board <= 3 = all (=='.') board
solve1dim ('.':board) = solve1dim board
solve1dim ('X':board) = solve1dim (flipfirst3 board)

countx str = length (filter (=='X') str)

solvemn 1 n strl = solve1dim (concat strl)
solvemn m 1 strl = solve1dim (concat strl)
solvemn 2 2 strl = countx (concat strl) `mod` 4 == 0
solvemn m n strl = countx (concat strl) `mod` 2 == 0

solve strl =
  let [m,n] = [read token :: Int | token <- words (head strl)]
  in solvemn m n (tail strl)

moin str = if solve (lines str) then "possible\n" else "impossible\n"
main = interact moin
