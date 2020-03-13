BEGIN{

    waiting=0
    dac=1000
    dac_readnextline=1001
    

    voltage=2000
    voltage_known=2001
    voltage_reading=2002
    

    adders=3000
    mode_known=3001
    adder_voltage_known=3002
    add_reading=3003
    
    analog_offset=4000
    analog_off_reading=4001

    offset=5000
    output_known=5001
    reading_MaxValues=5002
    reading_MinValues=5003
    reading_Noise=5004
    reading_Offset=5005

    status=waiting 

}

########################## HEADERS

/ASIC's Number:/{
    asic_id=$3
}

#####################################

/Start TEST DAC:/{
    status=dac
    next
}

status==dac && /Result of the /{
    which=$5
    channel=$7    
    gsub(":","",channel)
    status=dac_readnextline
    next
}

status==dac_readnextline{
    file="dac_test.txt"
    # Store in file : dac_test.txt
    # asic (P:=1 or N:=0) (channel A:=0 B:=1) six values (one per dac, one dac per discriminator and adder)  

 printf(int(asic_id) " " (which=="P"?1:0)) >> file
    for(i=1;i<=6;i++) gsub(",",".",$i)
    for(i=1;i<=6;i++) printf(" " $i) >> file
    print "" >> file

    close(file)

    status=dac
    next
}

/Result TEST  DAC/{
    status=waiting
}    

##########################

/Start TEST Voltage:/{
    status=voltage
    next
}

status==voltage && /Loop/ && /mV/{
   # print $0
    V=int($2)
    line_count=0
    #print "V=" V " mV"
    

    status=voltage_known
    next
}

status==voltage_known && /Matrix Response:/{
    status=voltage_reading
    next
}

status==voltage_reading && NF==6{
    file="voltage.txt"
    line_count++

    printf(int(asic_id) " " line_count " " 0 " " V) >> file
    for(i=1;i<=6;i++) gsub(",",".",$i)
    for(i=1;i<=3;i++) printf(" " $i*1.0) >> file
    print "" >> file
    printf(int(asic_id) " " line_count " " 1 " " V) >> file
    for(i=4;i<=6;i++) printf(" " $i*1.0) >> file
    print "" >> file

    close(file)


    if(line_count==7) status=voltage
    next
}

/Start TEST ADDER CHANNELS:/{
    status=adders
    next
}

status==adders && /Mode/{
   # print $0
    Mode=int($2)
   # print "Mode=" Mode

    status=mode_known
   
}

status==mode_known && /Loop/ && NF==2{
   # print $0 
    V=int($2)
   # print "V=" V " mV"

    status=adder_voltage_known
    next
}

status==adder_voltage_known && /Matrix Response/{
    status=add_reading
    next
}

status==add_reading && NF==6{
    file="adders.txt"
    
    
    printf(int(asic_id) " " Mode  " " 0 " " V) >> file
    for(i=1;i<=6;i++) gsub(",",".",$i)
    for(i=1;i<=3;i++) printf(" " $i) >> file
    print "" >> file
    printf(int(asic_id) " " Mode  " " 1 " " V) >> file
    for(i=4;i<=6;i++) printf(" " $i) >> file
    print "" >> file

    close(file)

    status=adders
    next
}

