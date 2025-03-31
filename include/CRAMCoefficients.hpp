#pragma once
#include <vector>
#include <complex>
#include "petscsystypes.h"

using Complex = std::complex<PetscReal>;

/**
 * This file holds the CRAM coefficients for the 
 * Incomplete Partial Fraction (IPF) method. 
 * 
 * These coefficients are from:
 * 
 * @cite Maria, P. (2016). Higher-Order Chebyshev 
 * Rational Approximation Method and Application 
 * to Burnup Equations. Nuclear Science and 
 * Engineering, 182(3), 297–318. 
 * https://doi.org/10.13182/NSE15-26
 */


class CRAMCoefficients
{
public:
    CRAMCoefficients(){};
    

    Complex theta(unsigned int i) const {return this->_thetas.at(i)};

    Complex alpha(unsigned int i) const {return this->_alphas.at(i)};

    PetscReal alpha0() const {return this->_alpha0};

protected:

    std::vector<Complex> _thetas;

    std::vector<Complex> _alphas;

    PetscReal _alpha0;
};

class CRAM4 : public CRAMCoefficients
{
    protected:

        const std::vector<Complex> _thetas = {Complex{-3.678453861815398e-1,  3.658121298678667   },
                                    Complex{ 1.548393223297122   ,  1.191822946627426   }};

        const std::vector<Complex> _alphas = {Complex{ 1.237660664064637e2 , -7.922222292656543e2 },
                                    Complex{ 1.156509240520614e1 ,  5.582759641139007e1 }};

        const PetscReal _alpha0= 8.652240695288853e-5;
};

class CRAM48 : public CRAMCoefficients
{
    const std::vector<Complex> _thetas = {Complex{-4.465731934165702e1	,  6.233225190695437e1 },
                                   Complex{-5.284616241568964	,  4.057499381311059e1 },
                                   Complex{-8.867715667624458	,  4.325515754166724e1 },
                                   Complex{ 3.493013124279215	,  3.281615453173585e1 },
                                   Complex{ 1.564102508858634e1	,  1.558061616372237e1 },
                                   Complex{ 1.742097597385893e1	,  1.076629305714420e1 },
                                   Complex{-2.834466755180654e1	,  5.492841024648724e1 },
                                   Complex{ 1.661569367939544e1	,  1.316994930024688e1 },
                                   Complex{ 8.011836167974721	,  2.780232111309410e1 },
                                   Complex{-2.056267541998229	,  3.794824788914354e1 },
                                   Complex{ 1.449208170441839e1	,  1.799988210051809e1 },
                                   Complex{ 1.853807176907916e1	,  5.974332563100539   },
                                   Complex{ 9.932562704505182	,  2.532823409972962e1 },
                                   Complex{-2.244223871767187e1	,  5.179633600312162e1 },
                                   Complex{ 8.590014121680897e-1,  3.536456194294350e1 },
                                   Complex{-1.286192925744479e1	,  4.600304902833652e1 },
                                   Complex{ 1.164596909542055e1	,  2.287153304140217e1 },
                                   Complex{ 1.806076684783089e1	,  8.368200580099821   },
                                   Complex{ 5.870672154659249	,  3.029700159040121e1 },
                                   Complex{-3.542938819659747e1	,  5.834381701800013e1 },
                                   Complex{ 1.901323489060250e1	,  1.194282058271408   },
                                   Complex{ 1.885508331552577e1	,  3.583428564427879   },
                                   Complex{-1.734689708174982e1	,  4.883941101108207e1 },
                                   Complex{ 1.316284237125190e1	,  2.042951874827759e1 }};

    const std::vector<Complex> _alphas = {Complex{ 6.387380733878774e2	, -6.743912502859256e2 },
                                   Complex{ 1.909896179065730e2	, -3.973203432721332e2 },
                                   Complex{ 4.236195226571914e2	, -2.041233768918671e3 },
                                   Complex{ 4.645770595258726e2	, -1.652917287299683e3 },
                                   Complex{ 7.765163276752432e2	, -1.783617639907328e4 },
                                   Complex{ 1.907115136768522e3	, -5.887068595142284e4 },
                                   Complex{ 2.909892685603256e3	, -9.953255345514560e3 },
                                   Complex{ 1.944772206620450e2	, -1.427131226068449e3 },
                                   Complex{ 1.382799786972332e5	, -3.256885197214938e6 },
                                   Complex{ 5.628442079602433e3	, -2.924284515884309e4 },
                                   Complex{ 2.151681283794220e2	, -1.121774011188224e3 },
                                   Complex{ 1.324720240514420e3	, -6.370088443140973e4 },
                                   Complex{ 1.617548476343347e4	, -1.008798413156542e6 },
                                   Complex{ 1.112729040439685e2	, -8.837109731680418e1 },
                                   Complex{ 1.074624783191125e2	, -1.457246116408180e2 },
                                   Complex{ 8.835727765158191e1	, -6.388286188419360e1 },
                                   Complex{ 9.354078136054179e1	, -2.195424319460237e2 },
                                   Complex{ 9.418142823531574e1	, -6.719055740098035e2 },
                                   Complex{ 1.040012390717851e2	, -1.693747595553868e2 },
                                   Complex{ 6.861882624343235e1	, -1.177598523430493e1 },
                                   Complex{ 8.766654491283722e1	, -4.596464999363902e3 },
                                   Complex{ 1.056007619389650e2	, -1.738294585524067e3 },
                                   Complex{ 7.738987569039419e1	, -4.311715386228984e1 },
                                   Complex{ 1.041366366475571e2	, -2.777743732451969e2 }};

    const PetscReal _alpha0 = 2.258038182743983e-47;
};
