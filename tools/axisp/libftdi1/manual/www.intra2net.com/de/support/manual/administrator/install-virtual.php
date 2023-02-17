<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Installation als virtuelle Maschine | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="install.php" title="Teil&nbsp;1.&nbsp;Installation"><link rel="prev" href="install-installation-appliance-software.php" title="3.4. Software"><link rel="next" href="install-virtual-vmware.php" title="5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="install-virtual.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="install-virtual.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">4. Kapitel - Installation als virtuelle Maschine</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="install-installation-appliance-software.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;1.&nbsp;Installation</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="install-virtual"></a>4. Kapitel - Installation als virtuelle Maschine</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="install-virtual.php#install-virtual-real">4.1. Vergleich mit echter Hardware</a></span></dt><dd><dl><dt><span class="sect2"><a href="install-virtual.php#install-virtual-real-fax">4.1.1. Ungleichm&auml;&szlig;ige Ausf&uuml;hrungsgeschwindigkeit</a></span></dt><dt><span class="sect2"><a href="install-virtual.php#install-virtual-real-io">4.1.2. Geringere I/O-Performance</a></span></dt><dt><span class="sect2"><a href="install-virtual.php#install-virtual-real-directnic">4.1.3. Kontakt mit ungefilterten Netzwerkpaketen</a></span></dt></dl></dd></dl></div><a class="indexterm" name="install-virtual-virtualisation"></a><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="install-virtual-real"></a>4.1. Vergleich mit echter Hardware</h2></div></div></div><p>Virtualisierungssysteme bringen im Vergleich zur Installation auf echter Hardware
            einige Vorteile wie z.B. Hardware-Konsolidierung, Energiesparen oder bessere
            Ausfallsicherheit durch Migrationsm&ouml;glichkeiten mit sich. Gleichzeitig kommt es
            allerdings auch zu den im Folgenden beschriebenen Nachteilen.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="install-virtual-real-fax"></a>4.1.1. Ungleichm&auml;&szlig;ige Ausf&uuml;hrungsgeschwindigkeit</h3></div></div></div><p>Das Betriebssystem kann nicht mehr selbst entscheiden, welche Prozesse wann genau
                ausgef&uuml;hrt werden sollen, denn die Virtualisierungsl&ouml;sung kann die Ausf&uuml;hrung des
                gesamten virtualisierten Systems anhalten oder verz&ouml;gern.</p><a class="indexterm" name="install-virtual-real-fax1"></a><p>Das Faxprotokoll G3 schreibt aber genaue Antwortzeiten vor. Da das virtualisierte
                System den Faxprozess nicht mehr entsprechend priorisieren und steuern kann, wird
                das Protokoll verletzt.</p><p>
                <span class="emphasis"><em>Daher ist Faxen auf einer virtuellen Maschine generell nicht
                    m&ouml;glich.</em></span>
            </p><a class="indexterm" name="d0e626"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="install-virtual-real-io"></a>4.1.2. Geringere I/O-Performance</h3></div></div></div><p>Das Betriebssystem kann nicht mehr direkt auf die Hardware von Netzwerkkarten oder
                Speichersystemen zugreifen, sondern muss hierf&uuml;r auf eine Funktion der
                Virtualisierungsl&ouml;sung zugreifen. Daf&uuml;r muss mehrfach zwischen Gast und Wirt
                umgeschaltet werden. Dies verringert nicht nur den maximal m&ouml;glichen Durchsatz,
                sondern erh&ouml;ht vor allem die Latenz.</p><p>Sind die Festplatten nicht lokal auf dem Virtualisierungsserver installiert,
                sondern z.B. &uuml;ber ein SAN angebunden, kommt noch die Latenz f&uuml;r den Transfer &uuml;ber
                das SAN hinzu. Auf verschiedenen SAN-L&ouml;sungen k&ouml;nnen aber sehr unterschiedliche
                Latenzzeiten beobachtet werden. L&ouml;sungen, die auf iSCSI basieren, tendieren eher zu
                hohen Latenzzeiten. L&ouml;sungen mit Fibre Channel oder FCoE (<span class="foreignphrase"><em class="foreignphrase">Fibre
                    Channel over Ethernet</em></span>) tendieren eher zu besseren Latenzzeiten.
                Durch zus&auml;tzliche Schichten wie z.B. Storage-Virtualisierung k&ouml;nnen noch zus&auml;tzliche
                Latenzen hinzukommen.</p><p>Die meisten Aufgaben eines Intranators werden typischerweise durch die Latenz von
                Festplattenzugriffen beschr&auml;nkt und nicht durch Festplattendurchsatz oder fehlende
                CPU-Leistung. Dieser Punkt kann die Leistung eines Intranators also merklich
                beeintr&auml;chtigen.</p><p>
                <span class="emphasis"><em>Wir empfehlen, dies durch den Einsatz schnellerer Festplatten (15.000 RPM)
                    oder Solid-State-Disks zu kompensieren.</em></span>
            </p><p>Au&szlig;erdem empfehlen wir das virtuelle Laufwerk f&uuml;r den Intranator nicht als dynamisch
                wachsend / bei Bedarf zugeteilt zu konfigurieren, sondern von Anfang an vollst&auml;ndig
                zuzuweisen und zu allokieren. Wenn das Laufwerk erst bei Bedarf w&auml;chst, kostet dies
                Performance bei Schreibzugriffen. Au&szlig;erdem werden zus&auml;tzliche
                Verwaltungsinformationen ben&ouml;tigt, die vor einem Zugriff erst abgerufen und danach
                evtl. angepasst werden m&uuml;ssen. Bei klassischen Festplatten werden durch die
                ungleichm&auml;&szlig;ige Aufteilung der Bl&ouml;cke zus&auml;tzliche Repositionierungen der Schreib-/Lesek&ouml;pfe
                ben&ouml;tigt.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="install-virtual-real-directnic"></a>4.1.3. Kontakt mit ungefilterten Netzwerkpaketen</h3></div></div></div><a class="indexterm" name="install-virtual-real-directnic-firewall"></a><p>Wird der Intranator als Router und Firewall eingesetzt und stellt damit die
                Verbindung zum Internet her, kommt er direkt mit Netzwerkpaketen aus dem Internet in
                Ber&uuml;hrung. Der Intranator ist daf&uuml;r konzipiert und kann mit nicht standardkonformen
                oder gar b&ouml;sartigen Paketen korrekt umgehen. Auch werden evtl. erkannte L&uuml;cken in
                den Treibern oder Funktionen zeitnah durch Updates geschlossen.</p><p>Wird der Intranator als virtuelle Maschine betrieben und seine Netzwerkkarten &uuml;ber
                die regul&auml;ren Netzwerkfunktionen eines Virtualisierungssystems verwaltet, dann wird
                das Virtualisierungssystem diesen Paketen ungefiltert ausgesetzt. Dies gilt
                normalerweise f&uuml;r den Netzwerkkartentreiber und den virtuellen Switch.</p><div class="mediaobject"><img src="../images/install/virtual-switch-danger.png"></div><p>Virtualisierungssysteme sind in der Regel nicht als Firewall konzipiert. Daher
                werden Updates der Treiber f&uuml;r die Netzwerkkarten und den virtuellen Switch nicht so
                kritisch eingestuft und dementsprechend weniger schnell verteilt und eingespielt.
                Dies erh&ouml;ht letztendlich das Risiko von St&ouml;rungen oder Angriffen.</p><p>Wir raten daher dringend davon ab, Netzwerkkarten, die direkt mit dem Internet
                verbunden sind, &uuml;ber die regul&auml;ren Netzwerkfunktionen des Virtualisierungssystems
                (typischerweise virtuelle Switches) anzubinden.</p><p><span class="emphasis"><em>Stattdessen empfehlen wir, die entsprechenden Netzwerkkarten als
                    komplette PCI-Ger&auml;te an die virtuelle Maschine durchzureichen.</em></span> Der
                Intranator steuert damit die Hardware &uuml;ber PCI-Zugriffe direkt an und die
                Virtualisierungsl&ouml;sung kommt gar nicht erst mit diesen Netzwerkpaketen in
                Ber&uuml;hrung.</p><div class="mediaobject"><img src="../images/install/virtual-nic-passthrough.png"></div><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Beachten Sie, dass diese Funktion nicht von allen Virtualisierungssystemen
                    angeboten wird und auch dann nur mit Unterst&uuml;tzung der Hardware (Intel VT-d bzw.
                    AMD-Vi in Prozessor und Chipsatz sowie passenden Beschreibungstabellen im BIOS) verf&uuml;gbar
                    ist. Pr&uuml;fen Sie daher bereits in der Planungsphase die Kompatibilit&auml;t.</p><p>Au&szlig;erdem ist beim Durchreichen von kompletten PCI-Ger&auml;ten in der Regel keine
                    Live-Migration der VM mehr m&ouml;glich. Eine VM muss daher vor einer Migration auf eine
                    andere Hardware erst heruntergefahren werden.</p></td></tr></table></div><p>Verwenden Sie alternativ eine zus&auml;tzliche Hardware-Firewall oder installieren den
                Intranator nicht als virtuelle Maschine, sondern auf dedizierter Hardware.</p><a class="indexterm" name="d0e679"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="install-installation-appliance-software.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="install.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">3.4. Software&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>