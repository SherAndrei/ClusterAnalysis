#include "KMeans.h"
#include <random>

#define N_ITER 10

void KMeans::find(const std::vector<Point>& points) {
    std::vector<Cluster> clusters;
    std::vector<Cluster> cur_clusters;
    std::vector<Cluster> res_clusters;
    double mu = 0;
    double min_mu = 1e9;
    double delta = 0;

    if (k != -1) {
        double min_mu_cur = 1e9;
        for (int i = 0; i < N_ITER; ++i) {
            cur_clusters.clear();
            cur_clusters.resize(k);
            mu = k_means(k, cur_clusters, points);
            if (mu < min_mu_cur) {
                min_mu_cur = mu;
                clusters = std::move(cur_clusters);
            }
        }
        _clusters = std::move(clusters);
        return;
    }

    for (size_t k = 1; k < 7; ++k) {
        clusters.clear();
        clusters.resize(k);

        double min_mu_cur = 1e9;
        for (int i = 0; i < N_ITER; ++i) {
            cur_clusters.clear();
            cur_clusters.resize(k);
            mu = k_means(k, cur_clusters, points);
            if (mu < min_mu_cur) {
                min_mu_cur = mu;
                clusters = std::move(cur_clusters);
            }
        }

        if (fabs(min_mu_cur - min_mu) > delta) {
            min_mu = min_mu_cur;
            delta = fabs(min_mu_cur - min_mu);
            res_clusters = std::move(clusters);
        }
    }
    _clusters = std::move(res_clusters);
}

double KMeans::k_means(size_t k, std::vector<Cluster>& clusters,
                                 const std::vector<Point>& points) {
    std::vector<int> points_cluster(points.size());
    std::vector<Point> cluster_centers(k);
    std::vector<int> clusters_size(k);

    double mu = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, points.size());
    for (size_t i = 0; i < k; ++i) {
        clusters_size[i] = 1;
        int a = dist(gen);
        cluster_centers[i] = points[a];
    }

    int going = 1;
    while (going) {
        going = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            double min_d = 1e9;
            int min_j = 0;
            for (size_t j = 0; j < k; ++j) {
                if (distance(points[i], cluster_centers[j]) < min_d) {
                    min_d = distance(points[i], cluster_centers[j]);
                    min_j = j;
                }
            }
            if (min_j != points_cluster[i]) going = 1;
            points_cluster[i] = min_j;
        }


        for (size_t i = 0; i < k; ++i)
            cluster_centers[i] = Point(0, 0);
        for (size_t i = 0; i < points.size(); ++i) {
            clusters_size[points_cluster[i]]++;
            cluster_centers[points_cluster[i]] += points[i];
        }

        for (size_t i = 0; i < k; ++i) {
             cluster_centers[i] /= (clusters_size[i]);
             clusters_size[i] = 1;
        }
    }
    clusters.resize(k);
    for (size_t i = 0; i < points.size(); ++i)
        clusters[points_cluster[i]].add(points[i]);

    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < clusters[i].points().size(); ++j) {
            for (size_t k = j + 1; k < clusters[i].points().size(); ++k) {
                mu += distance(clusters[i].points()[j], clusters[i].points()[k]);
            }
        }
        for (size_t j = i + 1; j < k; ++j) {
            mu += distance(cluster_centers[i], cluster_centers[j]);
       }
    }
    return mu;
}
