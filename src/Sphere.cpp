#include <Sphere.h>

Sphere::Sphere(Eigen::Vector3d &center, double R, std::shared_ptr<Material> mat) : m_R(R), m_center(center), m_mat(mat) {}

Eigen::Vector3d Sphere::normal(Eigen::Vector3d point) const { return (point - m_center)/m_R; }

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    Eigen::Vector3d oc = r.origin() - m_center;
    double a = r.direction().squaredNorm();
    double b = oc.dot(r.direction());
    double c = oc.squaredNorm() - m_R * m_R;
    double discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp > t_max || temp < t_min)
        {
            temp = (-b + sqrt(discriminant)) / a;
        }

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = normal(rec.p);
            rec.mat_ptr = m_mat;
            return true;
        }
    }
    return false;
}
