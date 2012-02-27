qsort [] = []
qsort (x:xs) = qsort [y | y <- xs, y<x ] ++ [x] ++ qsort[y | y <- xs, y>=x]

anwenden :: (a->b) -> [a] -> [b]
anwenden f [] = []
anwenden f (x:xs) = f x : anwenden f xs

inc n = n +1

quad = 1 : [2*length quad + 1 + head quad]

lookup :: Eq  a => a -> [(a,b)] -> [b]
lookup a c = [b | (d,b) <- c, a==d ]
