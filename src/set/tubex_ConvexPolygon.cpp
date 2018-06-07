/* ============================================================================
 *  tubex-lib - ConvexPolygon class
 * ============================================================================
 *  Copyright : Copyright 2017 Simon Rohou
 *  License   : This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 *
 *  Author(s) : Simon Rohou
 *  Bug fixes : -
 *  Created   : 2018
 * ---------------------------------------------------------------------------- */



/*
      void makeConvex();
      bool isClosed() const;
      const Point operator[](int point_id) const;

      bool operator==(const Polygon& p) const;
      bool operator!=(const Polygon& p) const;

      friend std::ostream& operator<<(std::ostream& str, const Polygon& p);
      static Polygon translate(const Polygon& p, const ibex::IntervalVector& box);
      friend Polygon operator&(const Polygon& p1, const Polygon& p2);

    protected:

      #ifdef _TUBES_POLYG_WITH_BOOST_
        Polygon(const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> >& p);
        Polygon(const boost::geometry::model::segment<boost::geometry::model::d2::point_xy<double> >& s);
        boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > m_polygon;
      #endif

      void createFromPoints(const std::vector<double>& v_x, const std::vector<double>& v_y);
      void createFromBoxes(const std::vector<ibex::IntervalVector>& v_boxes);

      friend class VibesFigure_Polygon;*/