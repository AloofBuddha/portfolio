import Data.List (inits, tails)

main :: IO ()
main = do
    print $ perms [1..4]
    print $ perms' "abcde"
    print $ perms'' [Nothing, Just 1, Just 2, Just 3]

perms, perms', perms'' :: [a] -> [[a]]

-- standard definition
perms []     = [[]]
perms (x:xs) = concatMap (spread x) (perms xs)

-- wait a minute, concatMap is the definition for bind on the List Monad
perms' []     = [[]]
perms' (x:xs) = perms' xs >>= spread x

-- abstracting out the pattern into a monadic foldr
perms'' = foldrM spread []

-- returns list of all possible ways to insert element into the list
-- it works by sandwiching the element between all different way of breaking
-- up the list into inits and tails
spread :: a -> [a] -> [[a]] 
spread el lst = zipWith (\x y -> x ++ [el] ++ y) (inits lst) (tails lst)

-- foldr equiv for Monadic operations
-- amazingly, this functions doesn't already exist in Control.Monad, so
-- lets write it ourselves!
foldrM :: (Monad m) => (a -> b -> m b) -> b -> [a] -> m b
foldrM _ z [] 	  = return z 
foldrM f z (x:xs) = do
	y <- foldrM f z xs
	f x y
