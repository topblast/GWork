import React from 'react';
import SectionBox from '../section-box';
import './why.styles.scss'


const WhySection = () => {
  return (
    <SectionBox id="why">
      <h2>Why the Caribbean?</h2>
      <div className='colored-line' />
      <p>The Caribbean, particularly CARICOM is a predominantly English-speaking grouping of countries comprising 16 million+ persons of which 60% are under the age of 30. The Caribbean boasts a high literacy rate, mature offshore industry and excellent Business IT infrastructure.</p>
      <br/>
      <p>We've found this largely untapped market in the international software space. Due to our deep connections with the local universities we've chosen Barbados as our first location.</p>
    </SectionBox>
  );
};

export default WhySection;