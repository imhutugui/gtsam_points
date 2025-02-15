#include <gtsam_points/registration/alignment.hpp>

#include <iostream>
#include <Eigen/Eigen>

namespace gtsam_points {

Eigen::Isometry3d align_points(
  const Eigen::Vector4d& target1,
  const Eigen::Vector4d& target2,
  const Eigen::Vector4d& target3,
  const Eigen::Vector4d& source1,
  const Eigen::Vector4d& source2,
  const Eigen::Vector4d& source3) {
  const Eigen::Vector4d mean_target = (target1 + target2 + target3) / 3.0;
  const Eigen::Vector4d mean_source = (source1 + source2 + source3) / 3.0;

  const Eigen::Matrix4d H = (target1 - mean_target) * (source1 - mean_source).transpose() +  //
                            (target2 - mean_target) * (source2 - mean_source).transpose() +  //
                            (target3 - mean_target) * (source3 - mean_source).transpose();

  Eigen::JacobiSVD<Eigen::Matrix3d> svd(H.block<3, 3>(0, 0), Eigen::ComputeFullU | Eigen::ComputeFullV);
  const auto& U = svd.matrixU();
  const auto& V = svd.matrixV();
  Eigen::Vector3d S = Eigen::Vector3d::Ones();

  const double det = U.determinant() * V.determinant();
  if (det < 0.0) {
    S(2) = -1;
  }

  Eigen::Isometry3d T_target_source = Eigen::Isometry3d::Identity();
  T_target_source.linear() = U * S.asDiagonal() * V.transpose();
  T_target_source.translation() = mean_target.head<3>() - T_target_source.linear() * mean_source.head<3>();

  return T_target_source;
}

Eigen::Isometry3d
align_points_4dof(const Eigen::Vector4d& target1, const Eigen::Vector4d& target2, const Eigen::Vector4d& source1, const Eigen::Vector4d& source2) {
  const Eigen::Vector4d mean_target = (target1 + target2) / 2.0;
  const Eigen::Vector4d mean_source = (source1 + source2) / 2.0;

  const Eigen::Matrix4d H = (target1 - mean_target) * (source1 - mean_source).transpose() +  //
                            (target2 - mean_target) * (source2 - mean_source).transpose();

  Eigen::JacobiSVD<Eigen::Matrix2d> svd(H.block<2, 2>(0, 0), Eigen::ComputeFullU | Eigen::ComputeFullV);
  const auto& U = svd.matrixU();
  const auto& V = svd.matrixV();
  Eigen::Vector2d S = Eigen::Vector2d::Ones();

  const double det = U.determinant() * V.determinant();
  if (det < 0.0) {
    S(1) = -1;
  }

  Eigen::Isometry3d T_target_source = Eigen::Isometry3d::Identity();
  T_target_source.linear().topLeftCorner<2, 2>(0, 0) = U * S.asDiagonal() * V.transpose();
  T_target_source.translation() = mean_target.head<3>() - T_target_source.linear() * mean_source.head<3>();

  return T_target_source;
}

}  // namespace gtsam_points
