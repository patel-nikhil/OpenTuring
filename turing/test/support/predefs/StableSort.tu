unit
module pervasive StableSort
    export isort, csort, rsort
    
    external "sort_stablesortint" procedure isort (arr : array 1 .. * of int, sz : int)
    external "sort_stablesortint" procedure csort (arr : array 1 .. * of char, sz : int)
    external "sort_stablesortreal" procedure rsort (arr : array 1 .. * of int, sz : int)
end StableSort
