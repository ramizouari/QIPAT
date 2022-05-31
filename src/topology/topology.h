#ifndef __TOPOLOGY_H__
#define __TOPOLOGY_H__
#include "algebra/abstract_algebra.h"
#include "linear_algebra/linear_algebra.h"
#include <functional>

namespace topology
{
    using namespace algebra;
    using namespace linalg;
    template<typename R>
    concept complex_type= requires(const R&r) {
        {r.real()} -> std::convertible_to<double>;
        {r.imag()} -> std::convertible_to<double>;
    };

    template<typename R>
    concept real_type= !complex_type<R>;

/*
* This class is the class of all metrics over E
* @Requirements
* None
*/
    template<typename E>
    struct metric_t
    {
        virtual real metric(const E&u,const E&v)const =0;
        real distance(const E& u, const E& v) const
        {
            return metric(u, v);
        }
    };


/*
* This class is the class of all norms over E
* @Requirements
* E is a vector space over a field
* @Notes
* Every specialisation of this class must define the norm consistently with the field K
*/
    template<typename E>
    struct norm_t :public metric_t<E>
    {
        virtual real norm(const E&u)const =0;
        real metric(const E&u,const E&v)const  override
        {
            return norm(v-u);
        }
    };

/*
* This class is the class of all inner products over E
* @Requirements
* 1. K is IC or IR
* 2. E is a vector space over E
* @Notes
* Every specialisation of this class must define the inner product consistently with the field K
*/

    template<typename K,typename E>
    struct inner_product_t:public norm_t<E>
    {
        real norm(const E&u) const override
        {
            return std::sqrt(std::abs(inner_product(u,u)));
        }

        virtual K inner_product(const E&u,const E&v)const  =0;
    };

/*
* This class defines the natural inner product over E
* @Requirements
* 1. K is IC or IR
* 2. E is a vector space over E
*/
    template<typename K,typename E>
    struct L2_inner_product;

    template<typename E>
    struct L2_inner_product<real,E>:public inner_product_t<real,E>
    {
        real inner_product(const E&u,const E&v) const
        {
            auto m=std::min(u.dim(),v.dim());
            real R=0;
            for(int i=0;i<m;i++)
                R+=u[i]*v[i];
            return R;
        }
    };

    template<typename E>
    struct L2_inner_product<IC,E>:public inner_product_t<IC,E>
    {
        IC inner_product(const E&u,const E&v) const
        {
            auto m=std::min(u.dim(),v.dim());
            IC R=0;
            for(int i=0;i<m;i++)
                R+=std::conj(u[i])*v[i];
            return R;
        }
    };

    template<typename E>
    struct L1_norm :public norm_t<E>
    {
        real norm(const E&u) const
        {
            real R=0;
            for(auto s:u)
                R+=std::abs(s);
            return R;
        }
    };

    template<typename E>
    struct L_inf_norm :public norm_t<E>
    {
        real norm(const E&u) const
        {
            real R=0;
            for(auto s:u)
                R=std::max(R,std::abs(s));
            return R;
        }
    };

    struct real_inner_product :public inner_product_t<real,real>
    {
        real inner_product(const real &u,const real &v) const override
        {
            return u*v;
        }
    };

    struct complex_inner_product :public inner_product_t<IC,IC>
    {
        IC inner_product(const IC &u,const IC &v) const override
        {
            return std::conj(u)*v;
        }
    };

    template<>
    struct L2_inner_product<real,real>:public real_inner_product{};
    template<>
    struct L_inf_norm<real>:public real_inner_product{};
    template<>
    struct L1_norm<real>:public real_inner_product{};

    template<>
    struct L2_inner_product<IC,IC>:public complex_inner_product{};

    template<typename E,typename F,typename R>
    class derivator
    {
        real eps;
    public:
        derivator(real _eps=1e-7):eps(_eps){}
        template<typename ...StructureMetaData>
        R jacobian(const std::function<F(E)>&f,E a,StructureMetaData ... meta_info) const
        {
            R J(0,meta_info...);
            for(int i=0;i<J.col_dim();i++)
            {
                a[i]+=eps;
                auto z2=f(a);
                a[i]-=2*eps;
                auto z1=f(a);
                auto du=(z2-z1)/(2*eps);
                for(int j=0;j<J.row_dim();j++)
                    J[j][i]=du[j];
                a[i]+=eps;
            }
            return J;
        }
    };

    template<typename E,real_type IK>
    class derivator<E,IK,E>
    {
        IK eps;
    public:
        derivator(IK _eps=1e-7):eps(_eps){}

        E gradient(const std::function<IK(E)>&f,E a) const
        {
            E grad(a);
            for(int i=0;i<grad.dim();i++)
            {
                a[i]+=eps;
                auto z2=f(a);
                a[i]-=2*eps;
                auto z1=f(a);
                a[i]+=eps;
                grad[i]=(z2-z1)/(2*eps);
            }
            return grad;
        }
    };

    template<real_type IK>
    class derivator<IK,IK,IK>
    {
        IK eps;
    public:
        derivator(IK _eps=1e-7):eps(_eps){}
        real derivative(const std::function<IK(IK)>&f,IK a) const
        {
            return (f(a+eps)-f(a-eps))/(2*eps);
        }

        real gradient(const std::function<IK(IK)>&f,IK a) const
        {
            return derivative(f,a);
        }
    };

    template<typename E,complex_type IK>
    class derivator<E,IK,E>
    {
        using real_type =typename IK::value_type;
        real eps;
    public:
        derivator(real_type _eps=1e-7):eps(_eps){}

        E gradient(const std::function<IK(E)>&f,E a) const
        {
            E grad(a);
            for(int i=0;i<grad.dim();i++)
            {
                a[i]+=eps;
                auto z2=f(a);
                a[i]-=2*eps;
                auto z1=f(a);
                a[i]+=eps;
                grad[i]=(z2-z1)/(2*eps);
            }
            return grad;
        }
    };

    template<complex_type IK>
    class derivator<IK,IK ,IK>
    {
        using real_type = typename IK::value_type;
        real_type eps;
    public:
        derivator(real_type _eps=1e-7):eps(_eps){}
        IC derivative(const std::function<IK(IK)>&f,IK a) const
        {
            return (f(a+eps)-f(a-eps))/(2*eps);
        }

        IC gradient(const std::function<IK(IK)>&f,IK a) const
        {
            return derivative(f,a);
        }
    };

    template<typename K,typename R,typename M,typename Norm=L2_inner_product<K,R>>
    class newton_raphson;

    template<typename Norm,real_type IK>
    class newton_raphson<IK,IK,IK,Norm>
    {
        inline static constexpr Norm N=Norm();
        derivator<IK, IK,IK> &D;
        real x0;
        real eps=1e-5;
    public:
        newton_raphson(real _x0, derivator<IK, IK, IK>& d) :D(d),x0(_x0) {}
        real root(const std::function<IK(IK)>& f) const
        {
            real x = x0;
            while (N.norm(f(x)) > eps)
                x = x - f(x) / D.derivative(f, x);
            return x;
        }
    };

    template<typename Norm,complex_type IK>
    class newton_raphson<IK,IK,IK,Norm>
    {
        inline static constexpr Norm N=Norm();
        derivator<IK, IK,IK> &D;
        IC x0;
        real eps=1e-5;
    public:
        newton_raphson(real _x0, derivator<IK, IK, IK>& d) :D(d),x0(_x0) {}
        IC root(const std::function<IK(IK)>& f) const
        {
            IC x = x0;
            while (N.norm(f(x)) > eps)
                x = x - f(x) / D.derivative(f, x);
            return x;
        }
    };

    template<real_type IK,typename E,typename M,typename Norm>
    class newton_raphson<IK,E,M,Norm>
    {
        inline static constexpr Norm N=Norm();
        derivator<E, E,M> &D;
        E x0;
        IK eps=1e-5;
    public:
        newton_raphson(E _x0, derivator<E, E, M>& d) :D(d),x0(_x0) {}
        template<typename ...StructureMetaData>
        E root(const std::function<E(E)>& f,StructureMetaData ... meta_info) const
        {
            E x = x0;
            while (N.norm(f(x)) > eps) {
                auto u=D.jacobian(f, x,meta_info...).solve(f(x));
                x-=u;
            }
            return x;
        }
    };


    template<complex_type IK,typename E,typename M,typename Norm>
    class newton_raphson<IK,E,M,Norm>
    {
        inline static constexpr Norm N=Norm();
        derivator<E, E,M> &D;
        E x0;
        real eps=1e-5;
    public:
        newton_raphson(E _x0, derivator<E, E, M>& d) :D(d),x0(_x0) {}
        template<typename ...StructureMetaData>
        E root(const std::function<E(E)>& f,StructureMetaData ... meta_info) const
        {
            E x = x0;
            while (N.norm(f(x)) > eps) {
                auto u=D.jacobian(f, x,meta_info...).solve(f(x));
                x-=u;
            }
            return x;
        }
    };

    template<typename Norm>
    class newton_raphson<IC,Norm,IC>
    {
        inline static constexpr Norm N=Norm();
        derivator<IC, IC,IC> &D;
        IC x0;
        real eps=1e-5;
    public:
        newton_raphson(IC _x0, derivator<IC, IC, IC>& d) :D(d),x0(_x0) {}
        IC root(const std::function<IC(IC)>& f) const
        {
            IC x = x0;
            while (N.norm(f(x)) > eps)
                x = x - f(x) / D.derivative(f, x);
            return x;
        }
    };

}
#endif