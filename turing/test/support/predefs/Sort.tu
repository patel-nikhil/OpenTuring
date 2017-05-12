unit
module pervasive Sort
    export isort, csort, rsort, ssort

    external "sort_sortint" procedure isort (arr : array 1 .. * of int, sz : int)
    external "sort_sortint" procedure csort (arr : array 1 .. * of char, sz : int)
    external "sort_sortreal" procedure rsort (arr : array 1 .. * of real, sz : int)
    external "sort_sortstring" procedure ssort (arr : array 1 .. * of string, sz : int)
end Sort
