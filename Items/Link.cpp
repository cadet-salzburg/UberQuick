#include "Link.h"
#include "FrameworkInlet.h"
#include "FrameworkOutlet.h"
#include "InterfaceInlet.h"
#include "InterfaceOutlet.h"
#include "StringModel.h"
#include "../system/System.h"
#include <QDebug>

namespace Uber {
    Point::Point(QPointF p)
    :QObject(nullptr)
    ,m_Point(p)
    {

    }

    QPointF Point::get() const
    {
        return m_Point;
    }

    void Point::set( const QPointF &p )
    {
        m_Point = p;
    }

    qreal Point::getX() const
    {
        return m_Point.x();
    }

    void Point::setX( const qreal &x )
    {
        m_Point.setX(x);
    }

    qreal Point::getY() const
    {
        return m_Point.y();
    }

    void Point::setY( const qreal &y )
    {
        m_Point.setY(y);
    }

    Link::Link()
    :m_Inlet( new BaseInlet() )
    ,m_Outlet( new BaseOutlet() )
    ,m_ConnectionOptions(nullptr)
    {
        QObject::connect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        QObject::connect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
    }

    Link::~Link()
    {
        if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            static_cast<Uber::FrameworkOutlet*>(m_Outlet)->getOutletHandle().unregisterFromNewData(*this, &Link::receivedData);
        }
        disconnectSignals();
    }

    void Link::setInlet( BaseInlet *inlet )
    {
        QObject::disconnect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        delete m_Inlet;
        m_Inlet = inlet;
        QObject::connect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        emit positionChanged();
    }

    void Link::setOutlet( BaseOutlet *outlet )
    {
        QObject::disconnect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        delete m_Outlet;
        m_Outlet = outlet;
        QObject::connect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        emit positionChanged();
    }

    BaseInlet *Link::getInlet()
    {
        return m_Inlet;
    }

    BaseOutlet *Link::getOutlet()
    {
        return m_Outlet;
    }

    void Link::addPoint( const QPointF &p )
    {
        m_Points.push_back(new Point(p) );
    }

    QObjectList Link::getPoints()
    {
        return m_Points;
    }

    /*
     * A link always starts from an outlet and ends at an inlet.
     * This is not affected by the way a connection is established
     */

    QPointF Link::getStartPos()
    {
        if ( m_Outlet )
        {
            return m_Outlet->getPosition();
        } else
        {
            return QPointF(0,0);
        }
    }

    QPointF Link::getEndPos()
    {
        if ( m_Inlet )
        {
            return m_Inlet->getPosition();
        } else
        {
            return QPointF(0,0);
        }
    }

    void Link::updatePosition( const QPointF& pos )
    {
        if ( m_Inlet->isValid() && m_Outlet->isValid() )
            return;
        if ( !m_Inlet->isValid() )
        {
            m_Inlet->setPosition(pos);
        } else if ( !m_Outlet->isValid() )
        {
            m_Outlet->setPosition(pos);
        }
    }

    bool Link::isValid()
    {
        if ( m_Inlet->getClassName() == "Uber::FrameworkInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            FrameworkInlet* inlet = qobject_cast<FrameworkInlet*>(m_Inlet);
            FrameworkOutlet* outlet = qobject_cast<FrameworkOutlet*>(m_Outlet);
            InletHandle inHandle = inlet->getInletHandle();
            OutletHandle outHandle = outlet->getOutletHandle();
            LinkHandle linkHandle = inHandle.link(outHandle);
            return linkHandle.isValid();
        } else if (  m_Inlet->getClassName() == "Uber::FrameworkInlet" && m_Outlet->getClassName() == "Uber::InterfaceOutlet")
        {
            return true;
        } else if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            return true;
        } else if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::InterfaceOutlet" )
        {
            return true;
        } else
        {
            return false;
        }
    }

    StringModel* Link::getConnectionTypename()
    {
        StringModel* options = nullptr;
        if (  m_Inlet->getClassName() == "Uber::FrameworkInlet" && m_Outlet->getClassName() == "Uber::InterfaceOutlet")
        {
            FrameworkInlet* inlet = qobject_cast<FrameworkInlet*>(m_Inlet);
            options =  inlet->getDataType();
        } else if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            FrameworkOutlet* outlet = qobject_cast<FrameworkOutlet*>(m_Outlet);
            options =  outlet->getDataType();
        }
        return options;
    }

    StringModel* Link::getConnectionOptions()
    {
        StringModel* options = nullptr;
        if (  m_Inlet->getClassName() == "Uber::FrameworkInlet" && m_Outlet->getClassName() == "Uber::InterfaceOutlet")
        {
            FrameworkInlet* inlet = qobject_cast<FrameworkInlet*>(m_Inlet);
            options =  inlet->getDataTypeFields();
        } else if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            FrameworkOutlet* outlet = qobject_cast<FrameworkOutlet*>(m_Outlet);
            options =  outlet->getDataTypeFields();
        }
        return options;
    }

    void Link::connectSignals()
    {
        QObject::connect(getOutlet(), SIGNAL(valueChanged(QVariant)),getInlet(), SIGNAL(valueChanged(QVariant)));
        QObject::connect(getOutlet(), SIGNAL(killSelf()),this, SLOT(remove()));
        QObject::connect(getInlet(), SIGNAL(killSelf()),this, SLOT(remove()));
        if ( m_Inlet->getClassName() == "Uber::InterfaceInlet" && m_Outlet->getClassName() == "Uber::FrameworkOutlet" )
        {
            static_cast<Uber::FrameworkOutlet*>(m_Outlet)->getOutletHandle().registerToNewData(*this, &Link::receivedData );
        }
    }

    void Link::disconnectSignals()
    {
        QObject::disconnect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        QObject::disconnect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        QObject::disconnect(getOutlet(), SIGNAL(valueChanged(QVariant)),getInlet(), SIGNAL(valueChanged(QVariant)));
        QObject::disconnect(getOutlet(), SIGNAL(killSelf()),this, SLOT(remove()));
        QObject::disconnect(getInlet(), SIGNAL(killSelf()),this, SLOT(remove()));
    }

    void Link::receivedData( std::shared_ptr<const _2Real::CustomType> data)
    {
        assert( data.get() );
        m_Mutex.lock();
        std::shared_ptr<const _2Real::Image> img =_2Real::Image::asImage(data);
        QVariant val = QVariant::fromValue(img);
        emit m_Outlet->valueChanged(val);
        m_Mutex.unlock();
    }

    bool Link::isFrameworkLink() const
    {
        if ( ( m_Inlet->getClassName() == QString("Uber::FrameworkInlet") ) && ( m_Outlet->getClassName() == QString("Uber::FrameworkOutlet") ) )
        {
            return true;
        } else {
            return false;
        }
    }
}
