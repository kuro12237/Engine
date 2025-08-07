#include "Terrain.h"

void CLEYERA::Manager::Terrain::Init() {
  modelManager_ = CLEYERA::Manager::ModelManager::GetInstance();
  renderManager_ = CLEYERA::Manager::RenderManager::GetInstance();
  colliderSystem_ = CLEYERA::Manager::ColliderSystem::GetInstance();
  objectManager_ = CLEYERA::Manager::ObjectManager::GetInstance();

  modelHandle_ = modelManager_->LoadModel(dfFilePath_, objName_);

  gameObj_ = std::make_shared<CLEYERA::Model3d::Game3dObject>();

  gameObj_->Create(modelHandle_);
  gameObj_->SetScale(scaleTerrain_);
  gameObj_->SetRotate(rotateTerrain_);
  gameObj_->SetTranslate(translateTerrain_);
  gameObj_->SetName(objName_);
  this->gameObj_->Update();

  renderManager_->PushObj(gameObj_);
  //objectManager_->AddObject(gameObj_);

  CLEYERA::Model3d::MeshData *meshData = gameObj_->GetModel().lock()->GetMeshData();
  CLEYERA::Model3d::system::VertexData data = meshData->GetData();
  size_t triangleCount = data.indecs.size() / 3;

  triCollider_.resize(triangleCount);

  for (size_t i = 0; i < triangleCount; i++) {
    for (size_t vert = 0; vert < 3; vert++) {
      size_t vertexIndex = data.indecs[i * 3 + vert];
      triCollider_[i].vertex[vert].x = data.vertices[vertexIndex].pos.x;
      triCollider_[i].vertex[vert].y = data.vertices[vertexIndex].pos.y;
      triCollider_[i].vertex[vert].z = data.vertices[vertexIndex].pos.z;
    }
  }

  line_ = std::make_shared<Model3d::Line3d>();
  line_->Init(triangleCount * 3);

  colors_.resize(triangleCount * 3 * 2);
  positions_.resize(triangleCount * 3 * 2);

  line_->SetLinePos(positions_);
  line_->SetLineColor(colors_);
  line_->SetRotate(rotateTerrain_);
  line_->SetTranslate(translateTerrain_);
  line_->SetScale(scaleTerrain_);
  line_->SetMat4x4(mat_);

  mat_.Identity();

  renderManager_->PushLine3d(line_);

  size_t index = 0;

  for (size_t i = 0; i < triangleCount; i++) {
    const auto &tri = triCollider_[i];
    using Vec3 = Math::Vector::Vec3;

    const Vec3 &v0 = tri.vertex[0];
    const Vec3 &v1 = tri.vertex[1];
    const Vec3 &v2 = tri.vertex[2];

    // v0 → v1
    positions_[index++] = v0;
    positions_[index++] = v1;

    // v1 → v2
    positions_[index++] = v1;
    positions_[index++] = v2;

    // v2 → v0
    positions_[index++] = v2;
    positions_[index++] = v0;
  }
  for (size_t i = 0; i < colors_.size(); i++) {
    colors_[i] = {0.0f, 0.0f, 0.0f, 1.0f};
  }
  line_->Update();
}

void CLEYERA::Manager::Terrain::Update() {

  for (size_t i = 0; i < triCollider_.size(); i++) {

    triCollider_[i].edgeVec[0] = triCollider_[i].vertex[1] - triCollider_[i].vertex[0];
    triCollider_[i].edgeVec[1] = triCollider_[i].vertex[2] - triCollider_[i].vertex[1];
    triCollider_[i].edgeVec[2] = triCollider_[i].vertex[0] - triCollider_[i].vertex[2];
    triCollider_[i].normal =
        Math::Vector::Func::Cross(triCollider_[i].edgeVec[0], triCollider_[i].edgeVec[1]);
    triCollider_[i].dot =
        Math::Vector::Func::Dot(triCollider_[i].normal * -1, triCollider_[i].vertex[0]);
  }
  gameObj_->Update();
}

void CLEYERA::Manager::Terrain::Finalize() {
  gameObj_.reset();
  line_.reset();
}

void CLEYERA::Manager::Terrain::CheckObjct() {
  for (size_t i = 0; i < triCollider_.size(); i++) {

    triCollider_[i].edgeVec[0] = triCollider_[i].vertex[1] - triCollider_[i].vertex[0];
    triCollider_[i].edgeVec[1] = triCollider_[i].vertex[2] - triCollider_[i].vertex[1];
    triCollider_[i].edgeVec[2] = triCollider_[i].vertex[0] - triCollider_[i].vertex[2];
    triCollider_[i].normal =
        Math::Vector::Func::Cross(triCollider_[i].edgeVec[0], triCollider_[i].edgeVec[1]);
    triCollider_[i].normal = Math::Vector::Func::Normalize(triCollider_[i].normal);
    triCollider_[i].dot =
        Math::Vector::Func::Dot(triCollider_[i].normal * -1, triCollider_[i].vertex[0]);
  }
  using Vec3 = Math::Vector::Vec3;

  for (size_t i = 0; i < triCollider_.size(); i++) {

    for (auto obj : objList_) {
      auto it = obj.lock();
      if (!it)
        continue;

      // 後で改善
      Vec3 pos = it->GetTranslate();

      // === ① 接地判定用レイ（下方向にだけチェック） ===

      // 線分の始点と終点を計算
      // yにsizeの-値
      Vec3 start = pos + Vec3{0.0f, -1.0f, 0.0f};
      Vec3 end = pos + Vec3{0.0f, 5.0f, 0.0f};

      // 三角形の平面の法線とDを計算
      Vec3 normal = triCollider_[i].normal;
      float d = triCollider_[i].dot;

      // 線分の始点と終点が三角形の平面のどちら側にあるかを判定
      float startDist = Math::Vector::Func::Dot(normal, start) + d;
      float endDist = Math::Vector::Func::Dot(normal, end) + d;

      // 両点が同じ側にある場合、交差しない
      if (startDist * endDist > 0) {
        continue;
      }

      // 線分が平面と交差する場合、交点を計算
      float t = startDist / (startDist - endDist);
      Vec3 intersection = start + (end - start) * t;

      if (triCollider_[i].contains(intersection)) {

        const float pushDistance = 0.01f;
        Vec3 pushedPos = intersection + normal * pushDistance;
        it->TerrainHit(pushedPos);
      }
    }
  }
}

void CLEYERA::Manager::Terrain::ChengeData(uint32_t modelHandle) {

  modelHandle_ = modelHandle;
  gameObj_->ChangeModel(modelHandle);

  CLEYERA::Model3d::MeshData *meshData = gameObj_->GetModel().lock()->GetMeshData();
  CLEYERA::Model3d::system::VertexData data = meshData->GetData();
  size_t triangleCount = data.indecs.size() / 3;
  triCollider_.clear();
  triCollider_.resize(triangleCount);

  for (size_t i = 0; i < triangleCount; i++) {
    for (size_t vert = 0; vert < 3; vert++) {
      size_t vertexIndex = data.indecs[i * 3 + vert];
      triCollider_[i].vertex[vert].x = data.vertices[vertexIndex].pos.x;
      triCollider_[i].vertex[vert].y = data.vertices[vertexIndex].pos.y;
      triCollider_[i].vertex[vert].z = data.vertices[vertexIndex].pos.z;
    }
  }
  line_ = std::make_shared<Model3d::Line3d>();
  line_->Init(triangleCount * 3);

  colors_.resize(triangleCount * 3 * 2);
  positions_.resize(triangleCount * 3 * 2);

  line_->SetLinePos(positions_);
  line_->SetLineColor(colors_);
  line_->SetRotate(rotateTerrain_);
  line_->SetTranslate(translateTerrain_);
  line_->SetScale(scaleTerrain_);
  line_->SetMat4x4(mat_);

  mat_.Identity();

  renderManager_->PushLine3d(line_);

  size_t index = 0;

  for (size_t i = 0; i < triangleCount; i++) {
    const auto &tri = triCollider_[i];
    using Vec3 = Math::Vector::Vec3;

    const Vec3 &v0 = tri.vertex[0];
    const Vec3 &v1 = tri.vertex[1];
    const Vec3 &v2 = tri.vertex[2];

    // v0 → v1
    positions_[index++] = v0;
    positions_[index++] = v1;

    // v1 → v2
    positions_[index++] = v1;
    positions_[index++] = v2;

    // v2 → v0
    positions_[index++] = v2;
    positions_[index++] = v0;
  }
  for (size_t i = 0; i < colors_.size(); i++) {
    colors_[i] = {0.0f, 0.0f, 0.0f, 1.0f};
  }
  line_->Update();
}
