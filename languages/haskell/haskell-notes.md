Haskell Notes
==============
Index
------
* [Language Constructs](#constructs)
* [Function/Library Reference](#functions)
* [GHC Interpreter](#ghci)

## TODO
* How to use all the numeric/logical/bit/comparison operators?

Misc
=======

* using `reads`, empty tuple `[]` signifies failure to read

        ghci> reads "" :: [(Integer,String)]
        []
        ghci> reads "abc34" :: [(Integer,String)]
        []
        ghci> reads "34" :: [(Integer,String)]
        [(34,"")]
        ghci> reads "   34" :: [(Integer,String)]
        [(34,"")]

Concepts
==========

* Haskell functions have no side effects, this is also called *referential transparency.* Such functions can be easily composed to construct more complex functions.

* Haskell is lazy. This goes well with referential transparency and makes you think of programs as **series of transformations on data.**

Language constructs <a name="constructs"></a>
========================================

comments
----------

    -- this is a haskell comment

functions
-------------
Function application has the highest precedence. A function name always starts with a small case. Features, syntax and semantics of fuctions is described below, case by case, with examples.

* Function definitions with optional type specification. Note that in some cases type specification might be necessary.

        doubleMe :: Num a => a -> a
        doubleMe x = x + x

        length' xs = sum [1 | _ <- xs]   

        removeNonUppercase st = [ c | c <- st, c `elem` ['A'..'Z']]   
        ghci> removeNonUppercase "IdontLIKEFROGS"  
        "ILIKEFROGS"

* list comprehension (TODO)

* Function order doesn't matter 
  ([it matters in case of a function's pattern matching cousins](#funcPattern))

        -- doubleMe is defined after doubleUs
        doubleUs x y = doubleMe x + doubleMe y
        doubleMe x = x + x

* Function order matters. <a name="funcPattern"></a> The sequence 2 will always return `"don't know"`. The "catch all" pattern should be last in any meaningful sequence of definitions.

        -- sequence 1
        spellit 7 = "seven"
        spellit x = "don't know"

        -- sequence 2
        spellit x = "don't know"
        spellit 7 = "seven"

* Function with guards,

        bmiTell :: (RealFloat a) => a -> String  
        bmiTell bmi  
            | bmi <= 18.5 = "You're underweight, you emo, you!"  
            | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"  
            | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"  
            | otherwise   = "You're a whale, congratulations!" 


let expressions
------------------

    ghci> let (a,b) = (12, 13); (c,d) = (10, 20) in a + b + c + d
    55

if expression
------------------

    doubleSmallNumber x = if x > 100  
                            then x  
                            else x*2 

Both, `then` and `else` parts are mandatory in the `if` expression, since it must return some value anyway (since it is an 'expression').

------------------------------------------------


Haskell functions/library <a name="functions"></a>
================================================
* Keywords: haskell library, haskell functions

predefined constants
-----------
* `otherwise :: Bool` is True
* `minBound :: Bounded a => a` depends on the bounded type
* `maxBound :: Bounded a => a` depends on the bounded type

general operators 
-----------------
* `*, +, - :: (Num a) => a -> a -> a` arithmetic operators 
* `(-1) :: Num a => a` negate a number, paranthesis are necessary
* `/ :: Fractional a => a -> a -> a` arithmetic division
* `div :: Integral a => a -> a -> a` integer division
* `mod :: Integral a => a -> a -> a` modulous operator
* `divMod :: Integral a => a -> a -> (a, a)` div and mod function in one
* `^ :: (Num a, Integral b) => a -> b -> a` exponent/power
* `** :: Floating a => a -> a -> a` exponent/power
* `True :: Bool, False :: Bool` boolean values
* `shiftL :: Bits a => a -> Int -> a` in `Data.Bits`, logical shift left
* `shiftR :: Bits a => a -> Int -> a` in `Data.Bits`, logical shift right
* `&& :: Bool -> Bool -> Bool` logical and
* `|| :: Bool -> Bool -> Bool` logical or
* `not :: Bool -> Bool` logical not
* `== :: (Eq a) => a -> a -> Bool` equality check
* `/= :: (Eq a) => a -> a -> Bool` equality check
* `<, <=, >=, > :: (Ord a) => a -> a -> Bool` inequality check
* `$ :: (a -> b) -> a -> b` function application
* `. :: (b -> c) -> (a -> b) -> a -> c` function composition

general functions
-----------------
* `id :: a -> a` an identity function
* `subtract :: Num a => a -> a -> a` for subtraction, since `-` operator cannot be curried.
* `succ :: (Enum a) => a -> a` returns successor
* `pred :: (Enum a) => a -> a` returns predecessor
* `max :: (Ord a) => a -> a -> a` 
* `min :: (Ord a) => a -> a -> a`
* `odd :: Integral a => a -> Bool`
* `even :: Integral a => a -> Bool`
* `div :: Integral a => a -> a -> a`
* `mod :: Integral a => a -> a -> a`
* `fromIntegral :: (Num b, Integral a) => a -> b`
* `show :: Show a => a -> String` converts data to a string
* `read :: Read a => String -> a` converts string to a specific data type, either given explicitly by type specification, or as inferred from the context.
* `compare :: (Ord a) => a -> a -> Ordering` evaluates to LT/EQ/GT
* `zip :: a -> b -> [(a,b)]`
* `flip :: (a -> b -> c) -> b -> a -> c`

math functions
--------------
* `negate :: Num a => a -> a` negate a number
* `abs :: Num a => a -> a` absolute value
* `ceiling :: (Integral b, RealFrac a) => a -> b`
* `floor :: (Integral b, RealFrac a) => a -> b`
* `round :: (Integral b, RealFrac a) => a -> b` converts 10.5 to 10??

list functions
-----------------
* `++ :: [a] -> [a] -> [a]` list append
* `:  :: a -> [a] -> [a]` the cons operator
* `!! :: [a] -> Int -> a` list indexing
* `<, <=, >=, > :: Ord a => a -> a -> Bool` comparison operators
* `==, /= :: Eq a => a -> a -> Bool` equality operators
* `head :: [a] -> a`
* `tail :: [a] -> [a]`
* `init :: [a] -> [a]`
* `last :: [a] -> a`
* `length :: Foldable t => t a -> Int`
* `null :: Foldable t => t a -> Bool` is the list null
* `reverse :: [a] -> [a]` reverse the list
* `take :: Int -> [a] -> [a]`
* `drop :: Int -> [a] -> [a]`
* `maximum :: (Ord a, Foldable t) => t a -> a`
* `minimum :: (Ord a, Foldable t) => t a -> a`
* `sum :: (Num a, Foldable t) => t a -> a`
* `product :: (Num a, Foldable t) => t a -> a`
* `elem :: (Eq a, Foldable t) => a -> t a -> Bool` membership check
* `cycle :: [a] -> [a]`
* `repeat :: a -> [a]`
* `replicate :: Int -> a -> [a]` first arg is the length of the returned list

* `takeWhile :: (a -> Bool) -> [a] -> [a]`
* `dropWhile :: (a -> Bool) -> [a] -> [a]`

places for pattern matching
------------------
* `func (x:xs) = ...` in function definitions
* `where (a,b) = ...` in where clause
* In let expressions,

        ghci> let len [] = 0; len (x:xs) = 1 + len xs in len [1,2,3,4,5]
        5

* `[a+b | (a,b) <- z]` in list comprehensions
* In case expressions,

        head' :: [a] -> a  
        head' xs = case xs of [] -> error "No head for empty lists!"  
                              (x:_) -> x  


------------------------------------------------



The Glasgow Haskell Compilation system Interpreter<a name="ghci"></a>
========================================

* Start the interpreter,

        $ ghci

* Load a haskell file `./file.hs` (use tab for auto completion),

        Prelude> :l file

* Reload the haskell file `./file.hs` after some changes,

        Prelude> :l file
  or

        Prelude> :r

* Change the prompt,

        Prelude> :set prompt "ghci> "
        ghci> 

* Query the type of an entity,

        ghci> :t (/)
        (/) :: Fractional a => a -> a -> a
        ghci> :t (-)
        (-) :: Num a => a -> a -> a
        ghci> :t (-1)
        (-1) :: Num a => a
        ghci> :t show
        show :: Show a => a -> String
        ghci> :t read
        read :: Read a => String -> a
        ghci> 

* See the definition of an entity (a type, typeclass, or function),

        ghci> :info length
        class Foldable (t :: * -> *) where
          ...
          length :: t a -> Int
          ...
          	-- Defined in ‘Data.Foldable’

        ghci> :info Int
        data Int = GHC.Types.I# GHC.Prim.Int# 	-- Defined in ‘GHC.Types’
        instance Bounded Int -- Defined in ‘GHC.Enum’
        instance Enum Int -- Defined in ‘GHC.Enum’
        instance Eq Int -- Defined in ‘GHC.Classes’
        instance Integral Int -- Defined in ‘GHC.Real’
        instance Num Int -- Defined in ‘GHC.Num’
        instance Ord Int -- Defined in ‘GHC.Classes’
        instance Read Int -- Defined in ‘GHC.Read’
        instance Real Int -- Defined in ‘GHC.Real’
        instance Show Int -- Defined in ‘GHC.Show’

        ghci> :info Num
        class Num a where
          (+) :: a -> a -> a
          (-) :: a -> a -> a
          (*) :: a -> a -> a
          negate :: a -> a
          abs :: a -> a
          signum :: a -> a
          fromInteger :: Integer -> a
          {-# MINIMAL (+), (*), abs, signum, fromInteger, (negate | (-)) #-}
          	-- Defined in ‘GHC.Num’
        instance Num Word -- Defined in ‘GHC.Num’
        instance Num Integer -- Defined in ‘GHC.Num’
        instance Num Int -- Defined in ‘GHC.Num’
        instance Num Float -- Defined in ‘GHC.Float’
        instance Num Double -- Defined in ‘GHC.Float’


