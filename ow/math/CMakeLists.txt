file(GLOB owmath_SRC
     "*.cpp"
)


add_library(owmath ${owmath_SRC})
#add_library(owmath OBJECT ${owmath_SRC})