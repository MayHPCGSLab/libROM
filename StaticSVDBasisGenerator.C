#include "StaticSVDBasisGenerator.h"

namespace CAROM {

StaticSVDBasisGenerator::StaticSVDBasisGenerator(
   int dim,
   int increments_per_time_interval,
   const std::string& basis_file_name,
   Database::formats file_format) :
   SVDBasisGenerator(basis_file_name, file_format),
   d_svdts(new StaticSVDTimeStepper(dim, increments_per_time_interval))
{
}

StaticSVDBasisGenerator::~StaticSVDBasisGenerator()
{
}

bool
StaticSVDBasisGenerator::isNextSnapshot(
   double time)
{
   return d_svdts->isNextStateCollection(time);
}

void
StaticSVDBasisGenerator::takeSnapshot(
   double* u_in,
   double time)
{
   if (d_basis_writer &&
       d_svdts->isNewTimeInterval() && getNumBasisTimeIntervals() > 0) {
      d_basis_writer->writeBasis();
   }
   d_svdts->collectState(u_in, time);
}

double
StaticSVDBasisGenerator::computeNextSnapshotTime(
   double* u_in,
   double* rhs_in,
   double time)
{
   return d_svdts->computeNextStateCollectionTime(u_in, rhs_in, time);
}

const Matrix*
StaticSVDBasisGenerator::getBasis()
{
   return d_svdts->getBasis();
}

int
StaticSVDBasisGenerator::getNumBasisTimeIntervals() const
{
   return d_svdts->getNumBasisTimeIntervals();
}

double
StaticSVDBasisGenerator::getBasisIntervalStartTime(
   int which_interval) const
{
   return d_svdts->getBasisIntervalStartTime(which_interval);
}

}