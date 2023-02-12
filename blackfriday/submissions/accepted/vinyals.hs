import Data.List
import Data.Maybe

takeunique x = map head (filter ((== 1) . length) (group . sort $ x))
maximum' [] = Nothing
maximum' x = Just (maximum x)
winner dice = maximum' (takeunique dice)

moin str = maybe "none" (show . (+1) . fromJust . (`elemIndex` dice)) (winner dice)
    where dice = [read token :: Int | token <- words ((lines str) !! 1)]

main = interact moin
