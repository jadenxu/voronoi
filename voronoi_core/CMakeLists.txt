SET(VORONOI_CORE_LIBS
    wpoint.h
    apollonius_dia.h
    apollonius_dia.cpp

    bf_apollonius.h
    bf_apollonius.cpp

    bf_relax.h
    bf_relax.cpp

    bf_voronoi.h
    bf_voronoi.cpp

    power_dia.h
    power_dia.cpp

    voronoi_dia.h
    voronoi_dia.cpp)

ADD_LIBRARY(voronoiCore ${VORONOI_CORE_LIBS})
TARGET_LINK_LIBRARIES(voronoiCore ${CORELIBS})
